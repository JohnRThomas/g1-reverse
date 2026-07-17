#include "g1_net_symbols.h"
/* net-core FUN_010317d4 @ 0x10317d4  (parity 300 trials PROVEN) */

extern void FUN_0102eb48(unsigned int a);

void FUN_010317d4(void)
{
  volatile unsigned char *base = (volatile unsigned char *)0x41016000;
  *(volatile unsigned int *)(base + 4) = 1;
  FUN_0102eb48(0x16);
  *(volatile unsigned int *)(base + 0x308) = 0x000f0003;
  *(volatile unsigned int *)(base + 0x348) = 0x000f0003;
  *(volatile unsigned int *)(0xe000e100 + 0x180) = 0x400000;
  return;
}
