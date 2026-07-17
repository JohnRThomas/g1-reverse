#include "g1_net_symbols.h"
/* net-core FUN_0101f7a8 @ 0x101f7a8  (parity 300 trials PROVEN) */

extern void FUN_010294d2(unsigned int, unsigned int);

void FUN_0101f7a8(void)
{
  unsigned int base = 0x21001230;

  FUN_010294d2(base + 0x20c, 0x21000500);
  FUN_010294d2(base + 0x210, 0x21000508);
  FUN_010294d2(base + 0x214, 0x210004f8);
}
