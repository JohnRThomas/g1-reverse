#include "g1_net_symbols.h"
/* net-core FUN_01008650 @ 0x1008650  (parity 300 trials PROVEN) */

extern void FUN_010083dc(void);
__attribute__((naked)) void FUN_01008650(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  __asm__ volatile(
    "push.w {r0, r4, r5, r6, r7, r8, r9, r10, r11, lr}\n"
    "sub sp, #0x1c\n"
    "bl FUN_010083dc\n"
    "ldr.w r8, [sp, #0x1c]\n"
    "add.w r8, r8, #0x20\n"
    "stm.w r8, {r0, r1, r2, r3, r4, r5, r6, r7}\n"
    "pop {r0, r1, r2, r3, r4, r5, r6, r7}\n"
    "stm.w r7, {r0, r1, r2, r3, r4, r5, r6, r11}\n"
    "pop.w {r4, r5, r6, r7, r8, r9, r10, r11, pc}\n"
  );
}

