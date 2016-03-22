#ifndef PCG_RANDOM_H
#define PCG_RANDOM_H 1

#include <ruby.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct pcg_rb_seed_t 
{
    uint64_t state;
    uint64_t seq;
} pcg_rb_seed_t;

extern VALUE rb_cPCGRandom;
extern pcg_rb_seed_t *pcg_rb_global_state;
extern bool _global_state_initialized;

#endif /* PCG_RANDOM_H */
