#include "g1_net_symbols.h"
/* net-core FUN_01018de8 @ 0x1018de8  (parity 300 trials PROVEN) */

typedef void (*fnptr)(void);
void FUN_01018de8(void)
{
  volatile unsigned char *base = (volatile unsigned char *)((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/;
  unsigned int p1 = *(volatile unsigned int *)(base + 0xc4);
  fnptr f = (fnptr)(*(volatile unsigned int *)(p1 + 4));
  f();
}

