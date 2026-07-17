#include "g1_net_symbols.h"
/* net-core FUN_0103735c @ 0x103735c  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

void FUN_0103735c(unsigned int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
  int *piVar1;
  int iVar2;

  if ((unsigned int)param_2 == 0x210043a8u) {
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x484);
    FUN_01039bb0(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x484);
  }
  iVar2 = param_2[0];
  piVar1 = (int *)param_2[1];
  *piVar1 = iVar2;
  *(int **)(iVar2 + 4) = piVar1;
  param_2[0] = 0;
  param_2[1] = 0;
  return;
}
