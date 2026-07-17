#include "g1_net_symbols.h"
/* net-core FUN_0100e934 @ 0x100e934  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_0100e944 = (volatile unsigned char *)((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
unsigned int FUN_0100e934(void)
{
  unsigned int x = DAT_0100e944[0x16] ^ 2;
  return (x >> 1) & 1;
}
