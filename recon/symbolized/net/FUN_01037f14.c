#include "g1_net_symbols.h"
/* net-core FUN_01037f14 @ 0x1037f14  (parity 300 trials PROVEN) */

extern unsigned int FUN_01037f00(void);

unsigned int FUN_01037f14(void)
{
    int *piVar4 = *(int **)((uintptr_t)&g_net_kernel_timeout_dlist_head) /*=0x21000750*/;
    unsigned int uVar1;
    unsigned int uVar3;
    int iVar2;
    if (piVar4 == (int*)((uintptr_t)&g_net_kernel_timeout_dlist_head) /*=0x21000750*/) {
        FUN_01037f00();
        return 0x7fffffff;
    } else {
        uVar1 = FUN_01037f00();
        if (piVar4 != 0) {
            uVar3 = piVar4[4] - uVar1;
            iVar2 = (piVar4[5] - ((int)uVar1 >> 0x1f)) - (unsigned int)((unsigned int)piVar4[4] < uVar1);
            if (iVar2 < (int)(unsigned int)(uVar3 < 0x80000000)) {
                if (-1 < iVar2) return uVar3;
                return 0;
            }
        }
    }
    return 0x7fffffff;
}

