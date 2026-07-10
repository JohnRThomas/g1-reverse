/* Reconstructed FUN_0007205c @ 0x7205c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int FUN_0007205c(unsigned int *param_1) {
    unsigned int cmp = (*(volatile uint32_t*)0x2000b450UL) | (unsigned int)(*(volatile uint8_t*)0x2000b458UL);
    int bVar1 = (*param_1 == cmp);
    if (bVar1) {
        *param_1 = 0;
    }
    return bVar1;
}

