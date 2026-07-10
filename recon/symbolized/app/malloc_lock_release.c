#include "g1_app_symbols.h"
/* named: malloc_lock_release */
/* Reconstructed malloc_lock_release @ 0x76ba8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lock_release_or_fatal(uint32_t);
void malloc_lock_release(void) {
    lock_release_or_fatal(((uintptr_t)&g_malloc_mutex) /*=0x20003804*/);
}

