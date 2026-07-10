#include "g1_net_symbols.h"
/* net-core FUN_01036128 @ 0x1036128  (parity 300 trials PROVEN) */

int FUN_01036128(unsigned int *param_1) {
  volatile unsigned char *base = (volatile unsigned char *)((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/;
  unsigned int v = *(volatile unsigned int *)(((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/ + 8) | (unsigned int)base[0x10];
  int bVar1 = (*param_1 == v);
  if (bVar1) *param_1 = 0;
  return bVar1;
}

