#include "g1_app_symbols.h"
/* named: env_lock_acquire */
/* Reconstructed env_lock_acquire @ 0x76bb4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lock_acquire_or_fatal(uint32_t);
void env_lock_acquire(void) {
    lock_acquire_or_fatal(((uintptr_t)&g_env_mutex) /*=0x20003818*/);
}

