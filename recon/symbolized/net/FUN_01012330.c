#include "g1_net_symbols.h"
/* net-core FUN_01012330 @ 0x1012330  (parity 300 trials PROVEN) */

char FUN_01012330(int param_1)
{
  char cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 != 0) {
    cVar1 = 1;
  }
  return cVar1;
}
