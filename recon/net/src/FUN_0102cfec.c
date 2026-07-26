/* net-core FUN_0102cfec @ 0x102cfec  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

void FUN_0102cfec(void)
{
  volatile unsigned int *p1 = (volatile unsigned int *)G1_NRF_IPC_NS_BASE;
  volatile unsigned int *p2 = (volatile unsigned int *)G1_NRF_RTC1_NS_BASE;
  *(volatile unsigned int *)((char*)p1 + 0x1ac) = *(volatile unsigned int *)((char*)p1 + 0x1ac) & 0x7fffffff;
  *(volatile unsigned int *)((char*)p2 + 0x14c) = 0;
  (void)*(volatile unsigned int *)((char*)p2 + 0x14c);
}

