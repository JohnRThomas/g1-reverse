#include "g1_net_symbols.h"
/* net-core FUN_010090f4 @ 0x10090f4  (parity 300 trials PROVEN) */

extern void FUN_0101f69c(void);

unsigned int FUN_010090f4(void)
{
  volatile unsigned char *p = (volatile unsigned char *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_0101f69c();
    return 0;
  }
  return 0xffffffff;
}
