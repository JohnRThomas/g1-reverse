#include "g1_net_symbols.h"
/* net-core FUN_01039c3c @ 0x1039c3c  (parity 300 trials PROVEN) */

extern unsigned int FUN_01039c20(int, unsigned int, unsigned int);
void FUN_01039c3c(int param_1, unsigned int param_2) {
  unsigned int uVar1 = FUN_01039c20(param_1, *(unsigned int *)(param_1 + 0xc), param_2);
  *(unsigned int *)(param_1 + 0xc) = uVar1;
  *(unsigned int *)(param_1 + 0x10) &= 0xfffffff7;
}

