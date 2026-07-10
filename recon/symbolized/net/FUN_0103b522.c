#include "g1_net_symbols.h"
/* net-core FUN_0103b522 @ 0x103b522  (parity 300 trials PROVEN) */
extern void FUN_01035e1c(int, int);

void FUN_0103b522(int param_1)
{
  int v;
  if (param_1 == 0) {
    return;
  }
  v = *(int *)(param_1 - 4);
  FUN_01035e1c(v, param_1 - 4);
}

