#include <ruby.h>
#include <stdint.h>
#include <pcg_variants.h>
#include <stdbool.h>

#include "pcg_random.h"
#include "pcg_seed.h"
#include "pcg_sfrand.h"

pcg_rb_seed_t pcg_rb_global_state;
bool _global_state_initialized;

/*
 * Initializes the global rng state with a seed.
 * @param seed The seed to use for initializing state & sequence. 
 *  Defaults to PCRandom.new_seed
 * 
 * @return last seed used for srand() or nil if this is the first time this
 *  is being called
 */
VALUE
pcg_func_srand(int argc, VALUE *argv, VALUE self)
{
    VALUE old_seed, seed;
    uint64_t state, seq;
    
    old_seed = _global_state_initialized ? pcg_rb_global_state.seed : Qnil;
    
    if(argc == 0)
    {
        seed = pcg_new_seed_bytestr(DEFAULT_SEED_BYTES * sizeof(uint8_t));
    }
    else
    {
        rb_scan_args(argc, argv, "01", &seed);
    }

    pcg_rb_set_seed(&pcg_rb_global_state, seed);
    
    memcpy(&state, pcg_rb_global_state.bytes, 
        ((pcg_rb_global_state.size) / 2) * sizeof(uint8_t));
    memcpy(&seq, pcg_rb_global_state.bytes + pcg_rb_global_state.size / 2, 
        ((pcg_rb_global_state.size) / 2) * sizeof(uint8_t));
    
    pcg32_srandom(state, seq);
    _global_state_initialized = true;
    return old_seed;
}

void
pcg_rb_set_seed(pcg_rb_seed_t *seed, VALUE seedval)
{
    seed->seed = seedval;
    // Currently only 16 byte seeds are supported.
    seed->size = DEFAULT_SEED_BYTES;
    pcg_rb_int_pack_bigendian_native_order(seed->seed, seed->bytes, 
        seed->size / sizeof(uint8_t), seed->size);

}

/**
 * Iniitalize the global rng state. Exits prematurely if already initialized
 * 
 * @return true if the global state was initialized with new values. false
 *  if the global state is already set, no changes are made in this scenario.
 */
bool
pcg_rb_init_global_state(void)
{
    if(_global_state_initialized)
    {
        return false;
    }
    uint64_t state, seq;
    
    VALUE seed = pcg_new_seed_bytestr(DEFAULT_SEED_BYTES);
    pcg_rb_set_seed(&pcg_rb_global_state, seed);

    memcpy(&state, pcg_rb_global_state.bytes, 
        ((pcg_rb_global_state.size) / 2) * sizeof(uint8_t));
    memcpy(&seq, pcg_rb_global_state.bytes + pcg_rb_global_state.size / 2, 
        ((pcg_rb_global_state.size) / 2) * sizeof(uint8_t));

    pcg32_srandom(state, seq);
    
    _global_state_initialized = true;
    return true;
}