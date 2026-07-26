/* net-core FUN_010209b8 @ 0x10209b8  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

volatile unsigned char *const DAT_010209c4 = (volatile unsigned char *)G1_NRF_TIMER0_NS_BASE;
void FUN_010209b8(void)
{
  *(volatile unsigned int *)(DAT_010209c4 + 0x540) = 0;
}

