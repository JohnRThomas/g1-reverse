#include "g1_net_symbols.h"
/* net-core FUN_0100d7bc @ 0x100d7bc  (parity 300 trials PROVEN) */

unsigned int FUN_0100d7bc(unsigned char *param_1)
{
  volatile unsigned char *flag = (volatile unsigned char *)((unsigned long)&g_net_esb_own_addr_valid) /*=0x21000ea8*/;
  if (*flag == 0) {
    volatile unsigned char *src = (volatile unsigned char *)((unsigned long)&g_net_esb_own_addr) /*=0x21000010*/;
    unsigned int w = *(volatile unsigned int *)src;
    unsigned char b = src[4];
    *(unsigned int *)param_1 = w;
    param_1[4] = b;
    return 1;
  }
  return 0;
}
