#include "g1_net_symbols.h"
/* net-core FUN_0100e018 @ 0x100e018  (parity 300 trials PROVEN) */

void FUN_0100e018(char *param_1, unsigned int *param_2)
{
  unsigned int v = *(unsigned int *)(param_1 + 3);
  param_2[0] = v;
  unsigned short h = *(unsigned short *)(param_1 + 7);
  *(unsigned short *)((char*)param_2 + 4) = h;
}

