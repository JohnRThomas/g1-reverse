#include "g1_app_symbols.h"
/* named: k_current_get */
/* Reconstructed k_current_get @ 0x748ac  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint32_t k_current_get(void) {
    return *(volatile uint32_t*)((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/;
}

