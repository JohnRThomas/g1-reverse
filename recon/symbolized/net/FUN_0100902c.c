#include "g1_net_symbols.h"
/* net-core FUN_0100902c @ 0x100902c  (parity 300 trials PROVEN) */

extern void FUN_0101f850(void);
extern void FUN_0102581c(unsigned int a);
extern void FUN_0100a7b0(void);

void FUN_0100902c(void)
{
  volatile unsigned char *base = (volatile unsigned char *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/;
  if (base[0x2c] != 0) {
    FUN_0101f850();
    FUN_0102581c(base[0x2e]);
  }
  FUN_0100a7b0();
  base[0x2c] = 0;
  return;
}
