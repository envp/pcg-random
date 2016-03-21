#include <ruby.h>
#include <pcg_variants.h>

#include "rb_constants.h"
#include "pcg_random.h"
#include "pcg_seed.h"

VALUE rb_cPCGRandom;

void
Init_pcg_random(void)
{
    /* Initialize constants used by C-code*/
    pcg_init_rb_constants();
    
    /* Define encapsulating class */
    rb_cPCGRandom = rb_define_class("PCGRandom", rb_cObject);
    
    /* Publicly expose constant for default seed size */
    rb_define_const(rb_cPCGRandom, "DEFAULT_SEED_BYTES", 
                    INT2FIX(DEFAULT_SEED_BYTES));
    
    /* Define seeding singleton methods under PCGRandom */
    rb_define_singleton_method(rb_cPCGRandom, "new_seed", pcg_func_new_seed, -1);
    rb_define_singleton_method(rb_cPCGRandom, "raw_seed", pcg_func_raw_seed, 1);
}