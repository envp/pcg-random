#ifndef PCG_RANDOM_H
#define PCG_RANDOM_H 1

#include <ruby.h>
#include <stdint.h>

extern VALUE rb_cPCGRandom;

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

#endif /* PCG_RANDOM_H */
