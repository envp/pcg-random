#ifndef PCG_RANDOM_H
#define PCG_RANDOM_H 1

#include <ruby.h>
#include <stdint.h>

typedef struct pcg_rb_seed_t 
{
    uint64_t initstate;
    uint64_t initseq;
} pcg_rb_seed_t;

extern VALUE rb_cPCGRandom;

#endif /* PCG_RANDOM_H */
