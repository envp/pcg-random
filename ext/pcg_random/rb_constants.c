#include <ruby.h>
#include "rb_constants.h"

VALUE pcg_rb_zero,
      pcg_rb_one;

void
pcg_init_rb_constants(void)
{
    // Commonly used ruby objects
    pcg_rb_zero = INT2FIX(0);
    pcg_rb_one  = INT2FIX(1);
}