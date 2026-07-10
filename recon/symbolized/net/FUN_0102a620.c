#include "g1_net_symbols.h"
/* net-core FUN_0102a620 @ 0x102a620  (parity 300 trials PROVEN) */

extern int FUN_0102d548(void);
extern void FUN_01039722(unsigned int, int);
unsigned int FUN_0102a620(void)
{
  volatile int *piVar1 = (volatile int*)((uintptr_t)&g_net_last_fault_code) /*=0x2100057c*/;
  if (*piVar1 == -0x10) {
    int iVar3 = FUN_0102d548();
    volatile unsigned int *puVar2 = (volatile unsigned int*)((uintptr_t)&g_net_fault_canary_flag) /*=0x20070000*/;
    if (iVar3 == -0x10) return 1;
    *piVar1 = iVar3;
    *puVar2 = 0xa5a5a5a5;
    if (*(volatile int*)((uintptr_t)&g_zephyr_log_level) /*=0x21000580*/ > 1) {
      FUN_01039722("s)" /*=0x103cd20*/, *piVar1);
    }
  }
  return 0;
}

