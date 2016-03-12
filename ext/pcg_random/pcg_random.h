#ifndef PCG_RANDOM_H
#define PCG_RANDOM_H 1

#include "ruby.h"
#include "pcg_variants.h"

extern VALUE pcg_mPCGRandom;

VALUE pcg_new_seed();

#endif /* PCG_RANDOM_H */
