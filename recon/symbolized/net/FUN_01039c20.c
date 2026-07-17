#include "g1_net_symbols.h"
/* net-core FUN_01039c20 @ 0x1039c20  (parity 300 trials PROVEN) */

unsigned int FUN_01039c20(int param_1, int param_2, int param_3)
{
  unsigned int uVar1 = (unsigned int)(param_3 + param_2);
  unsigned int uVar2 = *(unsigned int *)(param_1 + 0x24);
  if ((*(int *)(param_1 + 0x10) << 0x1f) < 0) {
    uVar1 = uVar1 & (uVar2 - 1);
  } else if (uVar2 <= uVar1) {
    uVar1 = uVar1 - uVar2;
  }
  return uVar1;
}
