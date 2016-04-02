#include <ruby.h>
#include <ruby/util.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <pcg_variants.h>

#include "pcg_random.h"
#include "pcg_seed.h"
#include "pcg_rng.h"

VALUE rb_cPCGRandom;

static void pcg_random_mark(void *ptr);
static void pcg_random_free(void *rand_data);

static size_t pcg_random_memsize(const void *ptr);

static VALUE pcg_rb_float64_rand(pcg32_random_t *rng);

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
    xfree(rand_data);
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
pcg_rb_rand_t *
pcg_get_rand_type(VALUE obj)
{
    pcg_rb_rand_t *ptr;
    TypedData_Get_Struct(obj, pcg_rb_rand_t, &pcg_rand_data_t, ptr);
    return ptr;
}

/*
 * Memory allocation function that is called by `new` before `initialize` is
 * The chain is similar to: `new -> allocate -> initialize`
 *
 * Returns an object wrapping a C struct, with default initializations
 */
VALUE
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
 * Initialize the requested instance using a pre-allocated ruby
 * object (TypedStruct). Sets the instance variables and relevant accessor
 * methods where applicable.
 *
 * @param seed [Fixnum, Bignum] The seed to use use for initilization
 * 
 * @raise TypeError unless parameters are Fixnum / Bignum
 */
VALUE
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

    if( !(RB_TYPE_P(seed, T_FIXNUM) || RB_TYPE_P(seed, T_BIGNUM)) )
    {
        rb_raise(rb_eTypeError,"Expected Fixnum or Bignum, found %s", 
            rb_obj_classname(seed));
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
 * Get a random string of the given length
 * 
 * @param max The upperbound on numbers to generate
 */
VALUE
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
 * Return a random number between 0 and 1
 *
 * @param max Upper bound for the rng or the range of values that are acceptable
 */
VALUE
pcg_func_rand(int argc, VALUE *argv, VALUE self)
{
    VALUE max, result;
    long ubound;
    double num, lim;
    pcg_rb_rand_t *rdata = pcg_get_rand_type(self);
    
    if(argc == 0)
    {
        return pcg_rb_float64_rand(rdata->rng);
    }
    
    rb_scan_args(argc, argv, "01", &max);
    
    switch(TYPE(max))
    {
        case T_FIXNUM:
            ubound = FIX2LONG(max);
            return LONG2FIX(pcg32_boundedrand_r(rdata->rng, ubound));
        case T_FLOAT:
            num = ldexp((double) pcg32_boundedrand_r(rdata->rng, UINT32_MAX), -32);
            lim = NUM2DBL(max);
            return DBL2NUM(num * lim);
        case T_BIGNUM:
            num = ldexp((double) pcg32_boundedrand_r(rdata->rng, UINT32_MAX), -32);
            result = rb_big_mul(max, DBL2NUM(num));
            return rb_funcall(result, rb_intern("floor"), 0);
            break;
        case T_NIL:
            rb_raise(rb_eArgError, "Invalid argument - nil");
            break;
        default:
            rb_raise(rb_eTypeError, "Argument of type %s not supported (yet)",
                rb_obj_classname(max));
    }
    return Qnil;
}

/*
 * Return a random number in [0, 1) with double precision rounded to the closest
 * multiple for 1/(2**64)
 */
static VALUE 
pcg_rb_float64_rand(pcg32_random_t *rng)
{
    double d = ldexp((double) pcg32_boundedrand_r(rng, UINT32_MAX), -32);
    return DBL2NUM(d);
}

/*
 * Compares two instances of the class, returns true if they had the same
 * initial state
 *  
 * @param other [Object] Object to compare this instance to
 * 
 * @return
 */
VALUE 
pcg_func_eql(VALUE self, VALUE other)
{
    VALUE s, o;
    if( !strcmp(rb_obj_classname(self), rb_obj_classname(other)) )
    {
        s = rb_iv_get(self, "@seed");
        o = rb_iv_get(other, "@seed");
        return rb_funcall(s, rb_intern("=="), 1, o);
    }
    return Qfalse;
}