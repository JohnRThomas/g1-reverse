#include "g1_app_symbols.h"
/* named: __malloc_unlock */
/* globals referenced:
//   0x200037f0  g_malloc_lock                
*/
/* Reconstructed __malloc_unlock @ 0x785c8  (parity: 300/300 trials, PROVEN) */

extern void lock_release_or_fatal(void *p);
void __malloc_unlock(void)
{
    lock_release_or_fatal((void*)((uintptr_t)&g_malloc_lock) /*=0x200037f0*/);
}

