#include <ruby.h>
#include <stdint.h>
#include <pcg_variants.h>
#include <stdbool.h>

#include "pcg_random.h"
#include "pcg_seed.h"
#include "pcg_sfrand.h"

static void pcg_init_global_rng(uint64_t initstate, uint64_t initseq);

pcg_rb_seed_t *pcg_rb_global_state;
bool _global_state_initialized;


/*
 * 
 * 
 */
VALUE
pcg_func_init_global_rng(int argc, VALUE *argv, VALUE self)
{
    VALUE seed, old_seed;
    uint64_t params[2];
    uint64_t old_params[2] = {
        pcg_rb_global_state->state, 
        pcg_rb_global_state->seq
    };
    
    if(_global_state_initialized)
    {
        old_seed = pcg_rb_int_unpack_bigendian_native_order(old_params, 2,
            sizeof(uint64_t));
        if(argc == 0)
        {
            pcg_init_global_rng_default();
        }
        else
        {
            rb_scan_args(argc, argv, "01", &seed);
            pcg_rb_int_pack_bigendian_native_order(seed, params, 2, 
                sizeof(uint64_t));
            pcg_init_global_rng(params[0], params[1]);
        }
    }
    else
    {
        old_seed = Qnil;
        pcg_init_global_rng_default();
    }
    return old_seed;
}

void
pcg_init_global_rng_default(void)
{
    pcg_rb_global_state = (pcg_rb_seed_t *) malloc(sizeof(pcg_rb_seed_t));
    pcg_func_entropy_getbytes((void *)pcg_rb_global_state, sizeof(pcg_rb_seed_t));
    pcg32_srandom(pcg_rb_global_state->state, pcg_rb_global_state->seq);
    _global_state_initialized = true;
}

static
void pcg_init_global_rng(uint64_t initstate, uint64_t initseq)
{
    pcg32_srandom(initstate, initseq);
    _global_state_initialized = true;
}