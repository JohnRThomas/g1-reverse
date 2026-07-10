#include "g1_net_symbols.h"
/* net-core FUN_01034650 @ 0x1034650  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern unsigned int FUN_01039bb0(unsigned int a, unsigned int b);

int FUN_01034650(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  if (param_1 > 7) {
    FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103e6ad) /*=0x103e6ad*/, 0x2aa, param_4, param_4);
    r0 = FUN_01039bb0(((uintptr_t)&rodata_103e6ad) /*=0x103e6ad*/, 0x2aa);
  }
  return (int)(r0 << 2) + 0x100;
}

