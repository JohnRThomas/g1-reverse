#include "g1_net_symbols.h"
/* net-core FUN_01009054 @ 0x1009054  (parity 300 trials PROVEN) */

unsigned int FUN_01009054(unsigned int *param_1)
{
  if (param_1 != (unsigned int *)0) {
    unsigned int *src = (unsigned int *)((uintptr_t)&rodata_103ebf5) /*=0x103ebf5*/;
    unsigned int *end = src + 5;
    do {
      *param_1 = *src;
      src++;
      param_1++;
    } while (src != end);
    return 0;
  }
  return 0xffffffea;
}

