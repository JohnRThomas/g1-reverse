#include "g1_net_symbols.h"
/* net-core FUN_010122fc @ 0x10122fc  (parity 300 trials PROVEN) */

__attribute__((naked)) unsigned int FUN_010122fc(int param_1, unsigned int param_2)
{
  __asm__ volatile(
    "ldrh r3, [r0, #2]\n"
    "tst.w r3, #0x18\n"
    "beq.n 0x1012308\n"
    "movs r0, #1\n"
    "bx lr\n"
  );
}

