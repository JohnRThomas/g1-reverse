/* Reconstructed FUN_0002953c @ 0x2953c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00086534(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_0002953c(void)
{
    int iVar1 = FUN_00086534(0x20007b1cU, 0, 5, 0, 0);
    if (iVar1 == 0) {
        *(volatile uint8_t *)0x20018d8aUL = 1;
    }
}

