#include <ruby.h>
#include <pcg_variants.h>
#include <stdbool.h>

#include "rb_constants.h"
#include "pcg_random.h"
#include "pcg_seed.h"
#include "pcg_sfrand.h"

VALUE rb_cPCGRandom;

pcg_rb_seed_t pcg_rb_global_state;
bool _global_state_initialized;

void
Init_pcg_random(void)
{
    /*************************************************
     *              Initializations                  *
     *************************************************/
    
    /* Constants used by C-code*/
    pcg_init_rb_constants();
    
    /* Set a default seed for the global RNG */
    pcg_rb_init_global_state();
    
    /*************************************************
     *              Public API definitions           *
     *************************************************/
    rb_cPCGRandom = rb_define_class("PCGRandom", rb_cObject);
    
    rb_define_const(rb_cPCGRandom, "DEFAULT_SEED_BYTES", INT2FIX(DEFAULT_SEED_BYTES));

    rb_define_singleton_method(rb_cPCGRandom, "new_seed", pcg_func_new_seed, 0);
    rb_define_singleton_method(rb_cPCGRandom, "raw_seed", pcg_func_raw_seed, 1);
    rb_define_singleton_method(rb_cPCGRandom, "srand", pcg_func_srand, -1);
}