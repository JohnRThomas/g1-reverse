#include "g1_net_symbols.h"
/* net-core FUN_0102d938 @ 0x102d938  (parity 300 trials PROVEN) */

__attribute__((naked)) void FUN_0102d938(void)
{
    __asm__ volatile(
        "push.w {r0, r1, r2, r4, r5, r6, r7, r8, sb, lr}\n\t"
        "mov r8, r1\n\t"
        "mov r5, r2\n\t"
        "ldr r6, [r0, #0x10]\n\t"
        "add.w r3, r6, #0x37c\n\t"
    );
}

