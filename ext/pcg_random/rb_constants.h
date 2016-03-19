#ifndef PCG_RB_CONSTANTS_H
#define PCG_RB_CONSTANTS_H 1

#include <ruby.h>

extern VALUE pcg_rb_zero,
             pcg_rb_one,
             pcg_rb_big_zero,
             pcg_rb_big_one;
             
extern ID pcg_rb_plus, 
          pcg_rb_mul;

void pcg_init_rb_constants(void);

#endif /* PCG_RB_CONSTANTS_H */
