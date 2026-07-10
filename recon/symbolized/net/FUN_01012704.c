#include "g1_net_symbols.h"
/* net-core FUN_01012704 @ 0x1012704  (parity 300 trials PROVEN) */

typedef void (*fnptr)(unsigned int);
void FUN_01012704(unsigned int param_1)
{
  volatile unsigned char *base = (volatile unsigned char *)((uintptr_t)&g_net_own_addr_info) /*=0x21000f20*/;
  *(volatile unsigned int *)(base + 0x2c) = param_1;
  unsigned int ptr1 = *(volatile unsigned int *)(base + 0x28);
  fnptr f = *(fnptr *)ptr1;
  f(param_1);
}

