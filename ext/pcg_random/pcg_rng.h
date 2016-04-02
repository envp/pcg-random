#ifndef PCG_RNG_H
#define PCG_RNG_H 1

#include <ruby.h>
#include <stdint.h>

struct pcg_rb_seed
{
    VALUE val;
    uint64_t state;
    uint64_t seq;
};

typedef struct
{
    struct pcg_rb_seed seed;
    pcg32_random_t *rng;
} pcg_rb_rand_t;


pcg_rb_rand_t *pcg_get_rand_type(VALUE obj);

VALUE pcg_random_alloc(VALUE klass);
VALUE pcg_func_init(int argc, VALUE *argv, VALUE self);
VALUE pcg_func_rand(int argc, VALUE *argv, VALUE self);
VALUE pcg_func_rand_bytes(VALUE self, VALUE size);
VALUE pcg_func_eql(VALUE self, VALUE other);

#endif /* PCG_RNG_H */