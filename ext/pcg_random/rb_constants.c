#include <ruby.h>
#include "rb_constants.h"

VALUE pcg_rb_zero,
      pcg_rb_one,
      pcg_rb_big_zero,
      pcg_rb_big_one;


ID  pcg_rb_plus,
    pcg_rb_mul;

void
pcg_init_rb_constants(void)
{
    // Commonly used ruby objects
    pcg_rb_zero = INT2FIX(0);
    pcg_rb_one  = INT2FIX(1);
    
    pcg_rb_big_zero = rb_uint2big(0);
    pcg_rb_big_one  = rb_uint2big(1);
    
    // Commonly called functions
    pcg_rb_plus = rb_intern("+");
    pcg_rb_mul  = rb_intern("*");
}