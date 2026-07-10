#include "g1_app_symbols.h"
/* named: z_spin_unlock_valid */
/* Reconstructed z_spin_unlock_valid @ 0x7205c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int z_spin_unlock_valid(unsigned int *param_1) {
    unsigned int cmp = (*(volatile uint32_t*)((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/) | (unsigned int)(*(volatile uint8_t*)((uintptr_t)&g_spinlock_validate_owner) /*=0x2000b458*/);
    int bVar1 = (*param_1 == cmp);
    if (bVar1) {
        *param_1 = 0;
    }
    return bVar1;
}

