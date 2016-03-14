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
    /* Initialize contants and IDs used by C-code*/
    pcg_init_rb_constants();
    
    rb_mPCGRandom = rb_define_module("PCGRandom");
    rb_define_module_function(rb_mPCGRandom, "new_seed", pcg_func_new_seed, 0);
}