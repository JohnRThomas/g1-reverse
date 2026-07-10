#include "g1_net_symbols.h"
/* net-core FUN_01033ca4 @ 0x1033ca4  (parity 300 trials PROVEN) */

void FUN_01033ca4(void)
{
  volatile unsigned char *p1 = (volatile unsigned char *)((uintptr_t)&g_154_dppi_channel_ack) /*=0x2100645c*/;
  volatile unsigned char *base = (volatile unsigned char *)REG_4100f000 /*=0x4100f000*/;
  unsigned char b = *p1;
  *(volatile unsigned int *)(base + 0x508) = 1u << b;
  *(volatile unsigned int *)(base + 0x5198) = 0;
  *(volatile unsigned int *)(base + 0xa080) = 0;
  return;
}

