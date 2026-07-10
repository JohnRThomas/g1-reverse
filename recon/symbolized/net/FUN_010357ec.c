#include "g1_net_symbols.h"
/* net-core FUN_010357ec @ 0x10357ec  (parity 300 trials PROVEN) */

extern void FUN_0103aec6(int a);
extern int FUN_0103ad1a(unsigned int a);
extern void FUN_0103aec2(int a);

int FUN_010357ec(int param_1)
{
    int iVar1;
    if (param_1 == 0) return (int)0xfffff82d;
    FUN_0103aec6(param_1 + 0x58);
    if (*(int*)(*(int*)(param_1+0xa0)+0x18) == 1) {
        iVar1 = FUN_0103ad1a(*(unsigned int*)(param_1+0xa8));
        iVar1 = iVar1 - 0x10;
        if (0 < iVar1) goto done;
    }
    iVar1 = (int)0xfffff82e;
done:
    FUN_0103aec2(param_1 + 0x58);
    return iVar1;
}

