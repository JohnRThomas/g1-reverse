#include "g1_net_symbols.h"
/* net-core FUN_010374dc @ 0x10374dc  (parity 300 trials PROVEN) */

extern void FUN_01036f74(unsigned int a);
extern void FUN_0103735c(unsigned int a, unsigned int b);

void FUN_010374dc(int param_1)
{
  if (*(volatile signed char *)(param_1 + 0xd) < 0) {
    *(volatile unsigned char *)(param_1 + 0xd) = *(volatile unsigned char *)(param_1 + 0xd) & 0x7f;
    FUN_0103735c(((uintptr_t)&g_zephyr_sched_thread_field) /*=0x21004b40*/, (unsigned int)param_1);
  }
  FUN_01036f74((unsigned int)(*(volatile int *)(((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/ + 8) == param_1));
  return;
}

