/* Reconstructed FUN_00065478 @ 0x65478  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00065434(void);
unsigned short FUN_00065478(void) {
    int iVar3 = FUN_00065434();
    unsigned short uVar1 = *(volatile uint16_t*)(0x20002bc0UL + (uint32_t)((iVar3 + 8) * 2));
    unsigned short uVar2 = uVar1 & 0x1c;
    if ((uVar1 & 0x1c) != 0) {
        uVar2 = 1;
    }
    return uVar2;
}

