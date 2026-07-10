#include "g1_app_symbols.h"
/* named: svc_attr_memory_release */
/* Reconstructed svc_attr_memory_release @ 0x7f3c2  (parity: 300/300 trials, PROVEN) */

extern void FUN_000868b4(void);

void svc_attr_memory_release(int param_1)
{
    unsigned int *puVar1;
    unsigned int uVar2;
    *(unsigned int*)(param_1 + 0x134) = 0;
    while ((puVar1 = *(unsigned int**)(param_1 + 0x150)) != (unsigned int*)0) {
        uVar2 = *puVar1;
        *(unsigned int*)(param_1 + 0x150) = uVar2;
        if (puVar1 == *(unsigned int**)(param_1 + 0x154)) {
            *(unsigned int*)(param_1 + 0x154) = uVar2;
        }
        FUN_000868b4();
    }
    *(unsigned int*)(param_1 + 0x158) = 0;
    return;
}

