#include "g1_net_symbols.h"
/* net-core FUN_0101e398 @ 0x101e398  (parity 300 trials PROVEN) */

extern int FUN_010280f2(unsigned int);
extern unsigned int FUN_0100f748(unsigned int);
extern unsigned int FUN_0100f70c(unsigned int);

int FUN_0101e398(unsigned int param_1)
{
    int iVar1 = FUN_010280f2(param_1);
    if (iVar1 == 0) return 0;
    iVar1 = FUN_010280f2(~param_1);
    if (iVar1 == 0) return 0;
    unsigned int uVar2 = (unsigned int)(((int)param_1 >> 0x1b) ^ ((int)param_1 >> 0x1a));
    if (((uVar2 - 1) & uVar2) == 0) return 0;
    uVar2 = param_1 & 0xff;
    uVar2 = uVar2 & (uVar2 - 1);
    if ((uVar2 & (uVar2 - 1)) == 0) return 0;
    uVar2 = FUN_0100f748(param_1 & 0xffff);
    if (uVar2 > 0xb) return 0;
    uVar2 = FUN_0100f70c(param_1);
    if (uVar2 > 0x18) return 0;
    if ((param_1 & 0xffff) == (param_1 >> 16) && (((param_1 ^ (param_1 >> 8)) & 0xff00ff) == 0)) return 0;
    unsigned int r3 = 0x8e89bed6u ^ param_1;
    return (((r3 - 1) & r3) != 0) ? 1 : 0;
}

