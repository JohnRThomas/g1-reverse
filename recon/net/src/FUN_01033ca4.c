/* net-core FUN_01033ca4 @ 0x1033ca4  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

void FUN_01033ca4(void)
{
  volatile unsigned char *p1 = (volatile unsigned char *)0x2100645c;
  volatile unsigned char *base = (volatile unsigned char *)G1_NRF_DPPIC_NS_BASE;
  unsigned char b = *p1;
  *(volatile unsigned int *)(base + 0x508) = 1u << b;
  *(volatile unsigned int *)(base + 0x5198) = 0;
  *(volatile unsigned int *)(base + 0xa080) = 0;
  return;
}

