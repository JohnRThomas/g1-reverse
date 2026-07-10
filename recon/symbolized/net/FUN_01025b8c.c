#include "g1_net_symbols.h"
/* net-core FUN_01025b8c @ 0x1025b8c  (parity 300 trials PROVEN) */

void FUN_01025b8c(void)
{
  volatile unsigned int *base = (volatile unsigned int *)REG_41008000 /*=0x41008000*/;
  base[0x180/4] = 0;
  base[0x184/4] = 0;
  base[0x18c/4] = 0;
  base[0x190/4] = 0;
  base[0x1ec/4] = 0;
  base[0x90/4] = 0;
  return;
}

