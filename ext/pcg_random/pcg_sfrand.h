#ifndef PCG_SFRAND_H
#define PCG_SFRAND_H 1

#include <ruby.h>

VALUE pcg_func_init_global_rng(int argc, VALUE *argv, VALUE self);
void pcg_init_global_rng_default(void);

#endif /* PCG_SFRAND_H */
