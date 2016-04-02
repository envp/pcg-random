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

void
Init_pcg_random(void)
{
    /* Constants / Classes */
    rb_cPCGRandom = rb_define_class("PCGRandom", rb_cObject);

    rb_define_const(rb_cPCGRandom, "DEFAULT_SEED_BYTES", INT2FIX(DEFAULT_SEED_BYTES));

    /* Singleton methods */
    rb_define_singleton_method(rb_cPCGRandom, "new_seed", pcg_func_new_seed, 0);
    rb_define_singleton_method(rb_cPCGRandom, "raw_seed", pcg_func_raw_seed, 1);

    /* Instance methods */
    rb_define_alloc_func(rb_cPCGRandom, pcg_random_alloc);
    rb_define_method(rb_cPCGRandom, "initialize", pcg_func_init, -1);
    
    rb_define_attr(rb_cPCGRandom, "seed", 1, 0);
    
    rb_define_method(rb_cPCGRandom, "rand", pcg_func_rand, -1);
    rb_define_method(rb_cPCGRandom, "bytes", pcg_func_rand_bytes, 1);
    
    rb_define_method(rb_cPCGRandom, "==", pcg_func_eql, 1);
}