#include "g1_net_symbols.h"
/* net-core FUN_01009184 @ 0x1009184  (parity 300 trials PROVEN) */

extern void FUN_010294ba(void);

unsigned int FUN_01009184(void)
{
  volatile unsigned char *p = (volatile unsigned char *)((uintptr_t)&g_net_layout_count_table) /*=0x21000a30*/;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_010294ba();
    return 0;
  }
  return 0xffffffff;
}

