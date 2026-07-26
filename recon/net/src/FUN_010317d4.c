/* net-core FUN_010317d4 @ 0x10317d4  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

extern void FUN_0102eb48(unsigned int a);

void FUN_010317d4(void)
{
  volatile unsigned char *base = (volatile unsigned char *)G1_NRF_RTC1_NS_BASE;
  *(volatile unsigned int *)(base + 4) = 1;
  FUN_0102eb48(0x16);
  *(volatile unsigned int *)(base + 0x308) = 0x000f0003;
  *(volatile unsigned int *)(base + 0x348) = 0x000f0003;
  *(volatile unsigned int *)(G1_NVIC_ISER0 + 0x180) = 0x400000;
  return;
}

