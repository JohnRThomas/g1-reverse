/* net-core FUN_01033c74 @ 0x1033c74  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

void FUN_01033c74(void)
{
  volatile unsigned char *p1 = (volatile unsigned char *)0x2100645c;
  volatile unsigned char *base = (volatile unsigned char *)G1_NRF_EGU0_NS_BASE;
  unsigned char b = *p1;
  unsigned int v = (unsigned int)b | 0x80000000u;
  *(volatile unsigned int *)(base + 0x198) = v;
  *(volatile unsigned int *)(base + 0x5000 + 0x80) = v;
  volatile unsigned char *p3 = (volatile unsigned char *)G1_NRF_DPPIC_NS_BASE;
  *(volatile unsigned int *)(p3 + 0x504) = 1u << b;
  return;
}

