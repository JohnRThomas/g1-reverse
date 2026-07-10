#include "g1_net_symbols.h"
/* net-core FUN_01018c58 @ 0x1018c58  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_01018c68 = (volatile unsigned char *)((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/;
signed char FUN_01018c58(void)
{
  unsigned int v = DAT_01018c68[0x3e];
  if (v != 0) v = 1;
  return (signed char)v;
}

