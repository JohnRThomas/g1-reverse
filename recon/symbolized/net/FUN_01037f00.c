#include "g1_net_symbols.h"
/* net-core FUN_01037f00 @ 0x1037f00 — true CFG extent 14 bytes (ends 0x1037f0e) */

extern int FUN_010317c0(void);

int FUN_01037f00(void)
{
  volatile unsigned int *p = (volatile unsigned int *)((unsigned long)&announce_remaining) /*=0x21004b6c*/;
  if (*p == 0) {
    return FUN_010317c0();
  }
  return 0;
}
