#include <pcg_variants.h>

#include "pcg_random.h"
#include "include/entropy.h"

VALUE pcg_mPCGRandom;

/*
 * Uses device entropy to create a new seed and return it under the Numeric
 * container, enclosing a 128 bit unsigned integer that is later broken down to 
 * seed the state initialization and generator of PCG
 */
VALUE pcg_new_seed()
{
    uint64_t seeds[2];
    entropy_getbytes((void*)seeds, sizeof(seeds));
    pcg128_t merged_seed = PCG_128BIT_CONSTANT(seeds[0], seeds[1]);
    return UINT2NUM(merged_seed);
}

void Init_pcg_random(void)
{
    pcg_mPCGRandom = rb_define_module("PCGRandom");
    rb_define_module_function(pcg_mPCGRandom, "new_seed", pcg_new_seed, 0);
}