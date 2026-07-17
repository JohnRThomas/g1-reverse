#include "g1_net_symbols.h"
/* net-core FUN_0100f7d0 @ 0x100f7d0  (parity 300 trials PROVEN) */

void FUN_0100f7d0(char *param_1, unsigned char param_2, unsigned char param_3)
{
  char *p = *(char **)(param_1 + 4) + 0xa8;
  *(unsigned char *)(p + 0xa3) = param_2;
  *(unsigned char *)(p + 0xa2) = param_3;
}
