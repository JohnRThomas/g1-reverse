#include "g1_net_symbols.h"
/* net-core FUN_010083a8 @ 0x10083a8  (parity 300 trials PROVEN) */

void FUN_010083a8(int *param_1,int *param_2,int param_3)
{
  int iVar5 = 4;
  do {
    int iVar3 = *param_2;
    int iVar4 = param_2[1];
    unsigned int uVar1 = (*param_1 - iVar3) & -param_3;
    unsigned int uVar2 = (param_1[1] - iVar4) & -param_3;
    *param_1 = *param_1 - uVar1;
    param_1[1] = param_1[1] - uVar2;
    param_1 = param_1 + 2;
    *param_2 = iVar3 + uVar1;
    param_2[1] = iVar4 + uVar2;
    param_2 = param_2 + 2;
    iVar5 = iVar5 - 1;
  } while (iVar5 != 0);
}

