#include "g1_app_symbols.h"
/* named: __errno_location */
/* Reconstructed __errno_location @ 0x71678  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int __errno_location(void)
{
    return *(volatile int32_t*)((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/ + 0x78;
}

