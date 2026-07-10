#include "g1_net_symbols.h"
/* net-core FUN_01033c74 @ 0x1033c74  (parity 300 trials PROVEN) */

void FUN_01033c74(void)
{
  volatile unsigned char *p1 = (volatile unsigned char *)((uintptr_t)&g_154_dppi_channel_ack) /*=0x2100645c*/;
  volatile unsigned char *base = (volatile unsigned char *)REG_41014000 /*=0x41014000*/;
  unsigned char b = *p1;
  unsigned int v = (unsigned int)b | 0x80000000u;
  *(volatile unsigned int *)(base + 0x198) = v;
  *(volatile unsigned int *)(base + 0x5000 + 0x80) = v;
  volatile unsigned char *p3 = (volatile unsigned char *)REG_4100f000 /*=0x4100f000*/;
  *(volatile unsigned int *)(p3 + 0x504) = 1u << b;
  return;
}

