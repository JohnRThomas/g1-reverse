/* net-core FUN_0101fcf4 @ 0x101fcf4  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

extern void FUN_01020088(unsigned int a);

void FUN_0101fcf4(void)
{
  FUN_01020088(2);
  volatile unsigned int *base = (volatile unsigned int *)G1_NRF_AAR_NS_BASE;
  volatile unsigned char *flag = (volatile unsigned char *)0x210014d8;
  *flag = 1;
  base[0x100/4] = 0;
  base[0x104/4] = 0;
  base[0x108/4] = 0;
  *base = 1;
  return;
}

