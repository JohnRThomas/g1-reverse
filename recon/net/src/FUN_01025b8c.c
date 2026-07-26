/* net-core FUN_01025b8c @ 0x1025b8c  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

void FUN_01025b8c(void)
{
  volatile unsigned int *base = (volatile unsigned int *)G1_NRF_RADIO_NS_BASE;
  base[0x180/4] = 0;
  base[0x184/4] = 0;
  base[0x18c/4] = 0;
  base[0x190/4] = 0;
  base[0x1ec/4] = 0;
  base[0x90/4] = 0;
  return;
}

