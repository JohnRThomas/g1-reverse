#include "g1_net_symbols.h"
/* net-core FUN_0102581c @ 0x102581c  (parity 300 trials PROVEN) */

extern unsigned int FUN_010256dc(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_0102581c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int idx = param_1;
  if (param_1 > 4) {
    idx = FUN_010256dc(0x69, 0x4f, param_3, param_4, param_4);
  }
  *(volatile unsigned char *)(((uintptr_t)&g_sdc_resource_pool_table) /*=0x21001c24*/ + idx * 8 + 4) = 0;
}

