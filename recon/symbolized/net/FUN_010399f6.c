#include "g1_net_symbols.h"
/* net-core FUN_010399f6 @ 0x10399f6  (parity 300 trials PROVEN) */
extern int FUN_01039768(void);
extern int FUN_0103973c(int, int, int);
extern void FUN_01039846(int, int);
extern void FUN_01039936(int, int, int);
extern void FUN_01039972(int, int);

void FUN_010399f6(int param_1, int param_2)
{
  int iVar1;
  int iVar2;
  unsigned int uVar3;
  unsigned int uVar4;

  iVar1 = FUN_01039768();
  iVar2 = FUN_0103973c(param_1, param_2 + iVar1, 1);
  if (-1 < (iVar2 << 0x1f)) {
    FUN_01039846(param_1, param_2 + iVar1);
    iVar1 = FUN_01039768();
    FUN_01039936(param_1, param_2, param_2 + iVar1);
  }
  iVar1 = FUN_0103973c(param_1, param_2, 0);
  uVar4 = 1;
  uVar3 = FUN_0103973c(param_1, param_2 - iVar1, 1);
  if ((uVar3 & uVar4) == 0) {
    FUN_01039846(param_1, param_2 - iVar1);
    iVar1 = FUN_0103973c(param_1, param_2, 0);
    FUN_01039936(param_1, param_2 - iVar1, param_2);
    iVar1 = FUN_0103973c(param_1, param_2, 0);
    param_2 = param_2 - iVar1;
  }
  FUN_01039972(param_1, param_2);
  return;
}
