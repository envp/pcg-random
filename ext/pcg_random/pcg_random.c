#include <ruby.h>
#include <pcg_variants.h>
#include <stdbool.h>

#include "rb_constants.h"
#include "pcg_random.h"
#include "pcg_seed.h"
#include "pcg_sfrand.h"

VALUE rb_cPCGRandom;

pcg_rb_seed_t *pcg_rb_global_state;
bool _global_state_initialized;

void
Init_pcg_random(void)
{
    /* Initialize constants used by C-code*/
    pcg_init_rb_constants();
    
    /* Initialize the global rng with some default random seed */
    pcg_init_global_rng_default();
    
    rb_cPCGRandom = rb_define_class("PCGRandom", rb_cObject);
    
    rb_define_const(rb_cPCGRandom, "DEFAULT_SEED_BYTES", INT2FIX(DEFAULT_SEED_BYTES));

    rb_define_singleton_method(rb_cPCGRandom, "new_seed", pcg_func_new_seed, -1);
    rb_define_singleton_method(rb_cPCGRandom, "raw_seed", pcg_func_raw_seed, 1);
    rb_define_singleton_method(rb_cPCGRandom, "srand", pcg_func_init_global_rng, -1);
}