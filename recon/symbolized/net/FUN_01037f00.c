#include "g1_net_symbols.h"
/* net-core FUN_01037f00 @ 0x1037f00  (parity 300 trials PROVEN) */

extern int FUN_01037f00_tail(void);

int FUN_01037f00(void)
{
  volatile unsigned int *p = (volatile unsigned int *)((uintptr_t)&announce_remaining) /*=0x21004b6c*/;
  if (*p == 0) {
    return FUN_01037f00_tail();
  }
  return 0;
}

