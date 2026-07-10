#include "g1_net_symbols.h"
/* net-core FUN_010343b8 @ 0x10343b8  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

void FUN_010343b8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  unsigned int r1 = param_2;
  if (param_2 == 0) {
    r1 = ((uintptr_t)&rodata_103e628) /*=0x103e628*/;
    r0 = "acking error (context area might be not valid)" /*=0x103d2a7*/;
    FUN_01039bbe(r0, r1, 0x44, param_4, param_4);
    r1 = 0x44;
    r0 = ((uintptr_t)&rodata_103e628) /*=0x103e628*/;
    FUN_01039bb0(r0, r1);
  }
  *(unsigned int *)(r1 + 0x80) = (r0 | 0x80000000);
  return;
}

