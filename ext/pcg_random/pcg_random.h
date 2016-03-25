#ifndef PCG_RANDOM_H
#define PCG_RANDOM_H 1

#include <ruby.h>
#include <stdint.h>
#include <stdbool.h>

#include "pcg_seed.h"

/* Struct to hold a pointer to bytestring & ruby seed value */
typedef struct pcg_rb_seed_t 
{
    VALUE seed;
    size_t size;
    uint8_t bytes[DEFAULT_SEED_BYTES];
} pcg_rb_seed_t;

extern VALUE rb_cPCGRandom;
extern pcg_rb_seed_t pcg_rb_global_state;
extern bool _global_state_initialized;

#endif /* PCG_RANDOM_H */
