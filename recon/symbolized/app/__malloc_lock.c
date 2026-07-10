#include "g1_app_symbols.h"
/* named: __malloc_lock */
/* globals referenced:
//   0x200037f0  g_malloc_lock                
*/
/* Reconstructed __malloc_lock @ 0x785bc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lock_acquire_or_fatal(uint32_t);
void __malloc_lock(void) {
    lock_acquire_or_fatal(((uintptr_t)&g_malloc_lock) /*=0x200037f0*/);
}

