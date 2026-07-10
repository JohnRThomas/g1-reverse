/* Reconstructed FUN_00065448 @ 0x65448  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00065434(void);

unsigned short FUN_00065448(void)
{
    int iVar1 = FUN_00065434();
    volatile uint16_t *base = (volatile uint16_t *)0x20002bc0UL;
    return base[iVar1 + 8] & 1;
}

