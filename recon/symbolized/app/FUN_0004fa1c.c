#include "g1_app_symbols.h"
/* named: FUN_0004fa1c */
/* Reconstructed FUN_0004fa1c @ 0x4fa1c  (parity: 300/300 trials, PROVEN) */

void FUN_0004fa1c(unsigned char *param_1)
{
    unsigned char *pbVar2 = param_1 - 1;
    do {
        pbVar2 = pbVar2 + 1;
        *pbVar2 = *(volatile unsigned char*)(((uintptr_t)&rodata_f1968) /*=0xf1968*/ + *pbVar2);
    } while (pbVar2 != param_1 + 0xf);
}

