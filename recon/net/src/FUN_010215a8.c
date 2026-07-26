/* net-core FUN_010215a8 @ 0x10215a8  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

void FUN_010215a8(unsigned int param_1)
{
  volatile unsigned int *a = (volatile unsigned int*)(G1_NRF_VREQCTRL_NS_BASE + 0x500);
  volatile unsigned int *b = (volatile unsigned int*)(G1_NRF_RADIO_NS_BASE + 0x50c);

  if ((int)param_1 > 0) {
    *a = 1;
    *b = (param_1 - 3) & 0xff;
  } else {
    *a = 0;
    *b = param_1 & 0xff;
  }
}

