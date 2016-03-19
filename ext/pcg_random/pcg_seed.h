#ifndef PCG_SEED_H
#define PCG_SEED_H 1

#include <ruby.h>
#include <stdbool.h>

VALUE pcg_func_new_seed(int argc, VALUE *argv, VALUE self);
bool pcg_func_entropy_getbytes(void* dest, size_t size);
VALUE pcg_func_raw_seed(VALUE self, VALUE byte_size);

#endif /* PCG_SEED_H */
