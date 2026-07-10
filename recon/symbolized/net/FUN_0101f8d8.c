#include "g1_net_symbols.h"
/* net-core FUN_0101f8d8 @ 0x101f8d8  (parity 300 trials PROVEN) */

volatile unsigned int *DAT_0101f8f0 = (volatile unsigned int *)((uintptr_t)&g_net_flags_bitmap64) /*=0x21000020*/;
unsigned int FUN_0101f8d8(void) {
  return (((*DAT_0101f8f0 << 0x17) >> 0x1f) << 1) | (((*DAT_0101f8f0 << 0x14) >> 0x1f) << 2) | 1;
}

