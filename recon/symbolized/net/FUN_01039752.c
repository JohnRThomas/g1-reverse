#include "g1_net_symbols.h"
/* net-core FUN_01039752 @ 0x1039752  (parity 300 trials PROVEN) */

void FUN_01039752(int param_1, int param_2, int param_3, unsigned int param_4) {
  int iVar1;
  iVar1 = param_1 + param_2 * 8;
  if (*(unsigned int *)(param_1 + 8) < 0x8000) {
    *(short *)(iVar1 + param_3 * 2) = (short)param_4;
  } else {
    *(unsigned int *)(iVar1 + param_3 * 4) = param_4;
  }
}

