#include "g1_net_symbols.h"
/* net-core FUN_0100f100 @ 0x100f100  (parity 300 trials PROVEN) */

unsigned short FUN_0100f100(char *param_1, unsigned int param_2)
{
  if ((param_2 & 0xc) == 0) {
    return *(unsigned short *)(param_1 + 0x12);
  }
  return 0xa90;
}
