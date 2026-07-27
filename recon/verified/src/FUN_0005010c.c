/* Reconstructed FUN_0005010c @ 0x5010c  (parity: 300/300 trials, PROVEN) */
#include "../../headers/g1_nrf_regs.h"

extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_0007e2ec(int a, int b);

void FUN_0005010c(int param_1, unsigned int param_2, int param_3, int param_4)
{
    int r0 = param_1;
    int r2 = param_3;
    int r3 = (int)(param_2 + 1U);
    signed char cVar1;
    int bVar5;

    if ((unsigned int)r3 > 7) {
        FUN_0007e2fa(0x99cbd, 0xf1bde, 0xf1ba8, 0x5c, param_4);
        r3 = 7;
        r2 = param_1;
        FUN_0007e2fa(0xf1bf9, (int)param_2, r2, r3, 0);
        r0 = FUN_0007e2ec(0xf1ba8, 0x5c);
    }
    r0 = (int)(signed char)r0;
    bVar5 = (r0 >= 0);
    if (bVar5) {
        r0 = r0 + (int)0xe0000000;
    } else {
        r2 = (int)G1_SCB_CCR;
    }
    r3 = r3 << 5;
    r3 = (unsigned char)r3;
    if (bVar5) {
        r0 = r0 + 0xe100;
        cVar1 = (signed char)r3;
        *(char *)(r0 + 0x300) = cVar1;
    } else {
        r0 = r0 & 0xf;
        cVar1 = (signed char)r3;
        *(char *)(r2 + r0) = cVar1;
    }
}

