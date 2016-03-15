#include <ruby.h>
#include <pcg_variants.h>
#include <inttypes.h>
#include <string.h>

#include "rb_constants.h"
#include "pcg_random.h"
#include "pcg_seed.h"

VALUE rb_mPCGRandom;

void
Init_pcg_random(void)
{
    /* Initialize constants used by C-code*/
    pcg_init_rb_constants();
    
    /* Define encapsulating module */
    rb_mPCGRandom = rb_define_module("PCGRandom");
    
    /* Define methods under PCGRandom */
    rb_define_module_function(rb_mPCGRandom, "new_seed", pcg_func_new_seed, 0);
    rb_define_module_function(rb_mPCGRandom, "raw_seed", pcg_func_raw_seed, 1);
}