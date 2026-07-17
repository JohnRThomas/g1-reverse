#include "g1_net_symbols.h"
/* net-core FUN_01039936 @ 0x1039936  (parity 300 trials PROVEN) */

extern int FUN_01039768(int owner, int index);
extern void FUN_010397a4(int a, int b, int c);
extern void FUN_01039752(int a, int b, int c, int d);

void FUN_01039936(int param_1, int param_2, int param_3)
{
    int iVar1 = FUN_01039768(param_1, param_2);
    int iVar2 = FUN_01039768(param_1, param_3);
    int iVar3;
    FUN_010397a4(param_1, param_2, iVar1+iVar2);
    iVar3 = FUN_01039768(param_1, param_3);
    FUN_01039752(param_1, param_3+iVar3, 0, iVar1+iVar2);
}
