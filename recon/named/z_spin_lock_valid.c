/* named: z_spin_lock_valid */
/* Reconstructed z_spin_lock_valid @ 0x72040  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int z_spin_lock_valid(unsigned int *param_1) {
    unsigned int v = *param_1;
    if (v != 0) {
        int iVar1 = (int)((v & 3) - *(volatile uint8_t*)0x2000b458UL);
        if (iVar1 != 0) iVar1 = 1;
        return iVar1;
    }
    return 1;
}

