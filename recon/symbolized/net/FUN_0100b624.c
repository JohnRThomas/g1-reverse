#include "g1_net_symbols.h"
/* net-core FUN_0100b624 @ 0x100b624  (parity 300 trials PROVEN) */

volatile unsigned char *DAT_0100b62c = (volatile unsigned char *)((uintptr_t)&g_net_radio_drv_ctx) /*=0x21000c48*/;
unsigned char FUN_0100b624(void)
{
  return DAT_0100b62c[0xc4];
}

