#include "g1_net_symbols.h"
/* net-core FUN_01039d80 @ 0x1039d80  (parity 300 trials PROVEN) */

extern unsigned long long FUN_01039c20(int *p0, int p1, int p2);

void FUN_01039d80(int *param_1, int param_2, int param_3)
{
    unsigned long long uVar2;
    int iVar1;
    uVar2 = FUN_01039c20(param_1, param_2, param_3);
    iVar1 = (int)(uVar2 >> 32);
    if (*param_1 == (int)uVar2) {
        *param_1 = iVar1;
        param_1[4] = param_1[4] & 0xfffffff7;
    } else {
        *(unsigned int *)(param_1[8] + (iVar1 << 2)) = (param_3 << 2) | 2;
        iVar1 = (int)FUN_01039c20(param_1, param_1[1], param_3);
        param_1[1] = iVar1;
    }
}
