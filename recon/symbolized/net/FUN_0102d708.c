#include "g1_net_symbols.h"
/* net-core FUN_0102d708 @ 0x102d708  (parity 300 trials PROVEN) */

__attribute__((naked)) void FUN_0102d708(void)
{
    __asm__ volatile(
        "push.w {r4, r5, r6, r7, r8, sb, sl, fp, lr}\n\t"
        "movs r3, #1\n\t"
        "mov sb, r0\n\t"
        "ldr r5, [r0, #0x10]\n\t"
        "ldr r6, [r0, #4]\n\t"
        "sub sp, #0x14\n\t"
        "add.w r7, r5, #0x37c\n\t"
    );
}

