#include "g1_net_symbols.h"
/* net-core FUN_01039846 @ 0x1039846  (parity 300 trials PROVEN) */

extern unsigned int FUN_01039768(void);
extern unsigned int FUN_010397d2(unsigned int a, unsigned int b);
extern void FUN_010397ea(unsigned int a, unsigned int b, unsigned int c);

void FUN_01039846(int param_1, unsigned int param_2)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;

  uVar3 = *(volatile unsigned int *)(param_1 + 8);
  iVar1 = FUN_01039768();
  if ((0x7fff < uVar3) && (iVar1 == 1)) {
    return;
  }
  uVar2 = FUN_010397d2(uVar3, iVar1);
  FUN_010397ea((unsigned int)param_1, param_2, uVar2);
  return;
}
