#ifndef PCG_SFRAND_H
#define PCG_SFRAND_H 1

#include <ruby.h>

VALUE pcg_func_srand(int argc, VALUE *argv, VALUE self);
void pcg_rb_set_seed(pcg_rb_seed_t *seed, VALUE seedval);
bool pcg_rb_init_global_state(void);
#endif /* PCG_SFRAND_H */
