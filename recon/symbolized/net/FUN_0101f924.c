#include "g1_net_symbols.h"
/* net-core FUN_0101f924 @ 0x101f924  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_0101f930 = (volatile unsigned char *)((uintptr_t)&g_net_radio_tx_power_level) /*=0x2100144a*/;
unsigned char FUN_0101f924(void)
{
  return *DAT_0101f930 & 7;
}

