#include <ruby.h>
#include <ruby/util.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <pcg_variants.h>

#include "pcg_random.h"
#include "pcg_seed.h"

VALUE rb_cPCGRandom;

static void pcg_random_mark(void *ptr);
static void pcg_random_free(void *rand_data);
static size_t pcg_random_memsize(const void *ptr);
static pcg_rb_rand_t *pcg_get_rand_type(VALUE obj);
static VALUE pcg_random_alloc(VALUE klass);
static VALUE pcg_func_init(int argc, VALUE *argv, VALUE self);
static VALUE pcg_func_get_state(VALUE self);
static VALUE pcg_func_get_seq(VALUE self);

/*
 * Structure wrapping our rng's data type's GC related functions
 */
static const rb_data_type_t pcg_rand_data_t = {
     "pcg_random",
    {
        pcg_random_mark,
        pcg_random_free,
        pcg_random_memsize,
    },
};

/*
 * Internal - Mark the internal seed value for garbage collection since a VALUE
 * inside a C struct is not marked by the GC automatically, and isn't freed
 * correctly either.
 */
static void
pcg_random_mark(void *ptr)
{
     rb_gc_mark(((pcg_rb_rand_t *) ptr)->seed.val);
}

/*
 * Internal - Free internal C-types in the `pcg_rb_rand_t` struct
 */
static void
pcg_random_free(void *rand_data)
{
    xfree(((pcg_rb_rand_t *) rand_data)->rng);
    xfree((pcg_rb_rand_t *)(rand_data));
}

/*
 * Internal - Get the size of a valid pcg_rb_rand_t pointer
 *
 * @return the size of `pcg_rb_rand_t` struct if it is initialized correctly.
 *  0 if given a NULL pointer
 */
static size_t
pcg_random_memsize(const void *ptr)
{
    return ptr ? sizeof(pcg_rb_rand_t) : 0;
}

/*
 * Internal - Helper function to get a pointer to a pcg_rb_rand_t struct given
 * an instance of the `PCGRandom` class
 *
 * Returns an object wrapping a C struct, with default initializations
 */
static pcg_rb_rand_t *
pcg_get_rand_type(VALUE obj)
{
    pcg_rb_rand_t *ptr;
    TypedData_Get_Struct(obj, pcg_rb_rand_t, &pcg_rand_data_t, ptr);
    return ptr;
}

/*
 * Memory allocation function that is called by new before `initialize` is
 * The chain is similar to: `new -> allocate -> initialize`
 *
 * Returns an object wrapping a C struct, with default initializations
 */
static VALUE
pcg_random_alloc(VALUE klass)
{
    pcg_rb_rand_t *rand_data;
    VALUE obj;
    /*
     * ISO C forbids braced-groups within expressions
     * See: http://stackoverflow.com/questions/1238016/
     */
    obj = __extension__ TypedData_Make_Struct(klass, pcg_rb_rand_t, &pcg_rand_data_t, rand_data);

    rand_data->seed.val     = INT2FIX(0);
    rand_data->seed.state   = 0;
    rand_data->seed.seq     = 0;
    rand_data->rng          = ALLOC(pcg32_random_t);

    return obj;
}

/*
 * Internal - Initialize the requested instance using a pre-allocated ruby
 * object (TypedStruct). Sets the instance variables and relevant accessor
 * methods where applicable.
 */
static VALUE
pcg_func_init(int argc, VALUE *argv, VALUE self)
{
    VALUE seed;
    uint64_t cseeds[2];
    pcg_rb_rand_t* rand_data = pcg_get_rand_type(self);

    if(argc == 0)
    {
        seed = DEFAULT_SEED_VALUE;
    }
    else
    {
        rb_scan_args(argc, argv, "01", &seed);
    }

    rb_integer_pack(seed, (void *) cseeds, 2, sizeof(uint64_t), 0,
        INTEGER_PACK_MSWORD_FIRST|INTEGER_PACK_NATIVE_BYTE_ORDER);

    rand_data->seed.val     = seed;
    rand_data->seed.state   = cseeds[0];
    rand_data->seed.seq     = cseeds[1];
    pcg32_srandom_r(rand_data->rng, cseeds[0], cseeds[1]);

    /* Add & set private instance variables */
    rb_iv_set(self, "@seed", seed);
    rb_iv_set(self, "state", LONG2NUM(rand_data->seed.state));
    rb_iv_set(self, "sequence", LONG2NUM(rand_data->seed.seq));
    return self;
}

/*
 * Internal - Private method to access internal rng state parameter
 * (Most significant word of seed)
 */
static VALUE
pcg_func_get_state(VALUE self)
{
    VALUE state;
    state = rb_iv_get(self, "state");
    return state;
}

/*
 * Internal - Private method to access internal rng state parameter
 * (Most significant word of seed)
 */
static VALUE
pcg_func_get_seq(VALUE self)
{
    VALUE seq;
    seq = rb_iv_get(self, "sequence");
    return seq;
}

/*
 * Get a random string of the given length
 * 
 * @param max The upperbound on numbers to generate, if not specified, outputs 
 *  defaults to [0, 1)
 */
static VALUE
pcg_func_rand_bytes(VALUE self, VALUE size)
{
    VALUE result;
    pcg_rb_rand_t *rdata = pcg_get_rand_type(self);
    size_t len = NUM2ULONG(size);
    char *str = ALLOC_N(char, len);
    
    for(int i = 0; i < len; ++i)
    {
        str[i] = (char) pcg32_boundedrand_r(rdata->rng, CHAR_MAX);
    }
    result = rb_str_new(str, len);
    xfree(str);
    return result;
}

/*
 * Return a random number between 0 and max value.
 * 
 * rand()           -> Float in [0, 1)
 * rand(integer)    -> integer
 * rand(float)      -> float
 * rand(range)      -> Rturns a random number where range.member?(number) is true
 *
 * @param max Upper bound for the rng or the range of values that are acceptable
 */
static VALUE
pcg_func_rand(int argc, VALUE *argv, VALUE self)
{
    VALUE max, tmp;
    long ubound;
    double num;
    pcg_rb_rand_t *rdata = pcg_get_rand_type(self);
    
    if(argc == 0)
    {
        return pcg_rb_float32_rand(rdata->rng);
    }
    
    rb_scan_args(argc, argv, "01", &max);
    
    if(NIL_P(max))
    {
        rb_raise(rb_eArgError, "Invalid argument - nil");
    }
    else if(FIXNUM_P(max))
    {
        ubound = FIX2LONG(max);
        return pcg32_boundedrand_r(rdata->rng, ubound);
    }
    else if(TYPE(max) == T_BIGNUM)
    {
        tmp = pcg_rb_float32_rand(rdata->rng);
        tmp = rb_big_mul(max, tmp);
        num = floor(RFLOAT_VALUE(tmp));
        if(FIXABLE(num))
        {
            return LONG2FIX((long) num);
        }
        return rb_dbl2big(num);
    }
    else if(TYPE(max) == T_FLOAT)
    {
        tmp = pcg_rb_float32_rand(rdata->rng);
        return rb_funcall(max, rb_intern("*"), 1, tmp);
        
    }
    else
    {
        rb_raise(rb_eArgError, 
            "Found %s. Expecting Fixnum, Bignum, or Float", 
            rb_obj_classname(max));
    }
}

/**
 * 
 */
VALUE 
pcg_rb_float32_rand(pcg32_random_t *rng)
{
    double d = ldexp((double) pcg32_boundedrand_r(rng, UINT32_MAX), -32);
    return DBL2NUM(d);
}

void
Init_pcg_random(void)
{
    /* Constants / Classes */
    rb_cPCGRandom = rb_define_class("PCGRandom", rb_cObject);

    rb_define_const(rb_cPCGRandom, "DEFAULT_SEED_BYTES", INT2FIX(DEFAULT_SEED_BYTES));

    /* Singleton methods */
    rb_define_singleton_method(rb_cPCGRandom, "new_seed", pcg_func_new_seed, 0);
    rb_define_singleton_method(rb_cPCGRandom, "raw_seed", pcg_func_raw_seed, 1);

    /* Public instance methods */
    rb_define_alloc_func(rb_cPCGRandom, pcg_random_alloc);
    rb_define_attr(rb_cPCGRandom, "seed", 1, 0);
    rb_define_method(rb_cPCGRandom, "rand", pcg_func_rand, -1);
    rb_define_method(rb_cPCGRandom, "bytes", pcg_func_rand_bytes, 1);
    // rb_define_method(rb_cPCGRandom, "initialize_copy", pcg_func_rand_copy, 1);
    // rb_define_method(rb_cPCGRandom, "==", pcg_func_equal, 1);

    /* Private instance methods */
    rb_define_method(rb_cPCGRandom, "initialize", pcg_func_init, -1);
    // rb_define_private_method(rb_cPCGRandom, "marshal_dump", pcg_func_dump, 0);
    // rb_define_private_method(rb_cPCGRandom, "marshal_load", pcg_func_load, 1);
    rb_define_private_method(rb_cPCGRandom, "state", pcg_func_get_state, 0);
    rb_define_private_method(rb_cPCGRandom, "sequence", pcg_func_get_seq, 0);
}