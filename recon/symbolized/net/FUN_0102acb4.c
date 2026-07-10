#include "g1_net_symbols.h"
/* net-core FUN_0102acb4 @ 0x102acb4  (parity 300 trials PROVEN) */

extern void FUN_01039722(unsigned int a);

unsigned int FUN_0102acb4(unsigned int param_1)
{
  *(unsigned int *)(param_1 + 0x60) = ((uintptr_t)&rodata_102b3ad) /*=0x102b3ad*/;
  *(unsigned int *)(param_1 + 0x64) = ((uintptr_t)&rodata_102b351) /*=0x102b351*/;
  *(volatile unsigned int *)((uintptr_t)&g_net_0x21004604_flag) /*=0x21004604*/ = param_1;
  if (*(volatile int *)((uintptr_t)&g_zephyr_log_level) /*=0x21000580*/ > 1) {
    FUN_01039722("ut.c" /*=0x103cf0b*/);
  }
  return 0;
}

