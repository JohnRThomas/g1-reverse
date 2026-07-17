#include "g1_net_symbols.h"
/* net-core FUN_010397d2 @ 0x10397d2  (parity 300 trials PROVEN) */

extern int FUN_010397c0(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
int FUN_010397d2(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4) {
  int iVar1 = FUN_010397c0(param_1, 1, param_2, param_4, param_4);
  return 0x1f - __builtin_clz((unsigned int)((param_2 + 1) - iVar1));
}
