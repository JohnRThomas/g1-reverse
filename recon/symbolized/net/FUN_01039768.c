#include "g1_net_symbols.h"
/* net-core FUN_01039768 @ 0x1039768  (parity 300 trials PROVEN) */

extern unsigned int FUN_0103973c(void);
__attribute__((naked)) unsigned int FUN_01039768(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  __asm__ volatile(
    "movs r2, #1\n"
    "push {r3, lr}\n"
    "bl FUN_0103973c\n"
    "lsrs r0, r2\n"
    "pop {r3, pc}\n"
  );
}

