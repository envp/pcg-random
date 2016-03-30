#ifndef PCG_SEED_H
#define PCG_SEED_H 1

#include <ruby.h>
#include <stdbool.h>

#ifndef DEFAULT_SEED_BYTES
#   define DEFAULT_SEED_BYTES 16
#endif

#ifndef DEFAULT_SEED_VALUE
#   define DEFAULT_SEED_VALUE pcg_new_seed_bytestr(DEFAULT_SEED_BYTES * sizeof(uint8_t))
#endif

bool pcg_func_entropy_getbytes(void* dest, size_t size);

VALUE pcg_func_new_seed(VALUE self);
VALUE pcg_new_seed_bytestr(unsigned long seed_size);

VALUE pcg_func_raw_seed(VALUE self, VALUE byte_size);
VALUE pcg_raw_seed_bytestr(size_t size);

#endif /* PCG_SEED_H */
