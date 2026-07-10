#include "g1_net_symbols.h"
/* net-core FUN_0103610c @ 0x103610c  (parity 300 trials PROVEN) */

int FUN_0103610c(unsigned int *param_1) {
  volatile unsigned char *DAT_01036124 = (volatile unsigned char *)((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/;
  if (*param_1 != 0) {
    int iVar1 = (*param_1 & 3) - (unsigned int)DAT_01036124[0x10];
    if (iVar1 != 0) iVar1 = 1;
    return iVar1;
  }
  return 1;
}

