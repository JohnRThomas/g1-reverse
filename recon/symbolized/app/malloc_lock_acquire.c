#include "g1_app_symbols.h"
/* named: malloc_lock_acquire */
/* Reconstructed malloc_lock_acquire @ 0x76b9c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lock_acquire_or_fatal(uint32_t);
void malloc_lock_acquire(void) {
    lock_acquire_or_fatal(((uintptr_t)&g_malloc_mutex) /*=0x20003804*/);
}

