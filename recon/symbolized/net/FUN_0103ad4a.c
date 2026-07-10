#include "g1_net_symbols.h"
/* net-core FUN_0103ad4a @ 0x103ad4a  (parity 300 trials PROVEN) */

extern void FUN_0103689c(void);
__attribute__((naked)) void FUN_0103ad4a(unsigned int param_1, unsigned int param_2)
{
  __asm__ volatile(
    "mov.w r2, #-1\n"
    "mov.w r3, #-1\n"
    "b.w FUN_0103689c\n"
  );
}

