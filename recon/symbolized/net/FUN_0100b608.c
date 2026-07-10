#include "g1_net_symbols.h"
/* net-core FUN_0100b608 @ 0x100b608  (parity 300 trials PROVEN) */

volatile unsigned char *DAT_0100b610 = (volatile unsigned char *)((uintptr_t)&g_net_radio_drv_ctx) /*=0x21000c48*/;
unsigned char FUN_0100b608(void)
{
  return DAT_0100b610[0xb0];
}

