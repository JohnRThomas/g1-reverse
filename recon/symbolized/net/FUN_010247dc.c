#include "g1_net_symbols.h"
/* net-core FUN_010247dc @ 0x10247dc  (parity 300 trials PROVEN) */
/* net-core FUN_010247dc @ 0x10247dc  (parity 300 trials PROVEN) */
/* net-core FUN_010247dc @ 0x10247dc  (parity 300 trials PROVEN) */

extern int FUN_01024b20(int);
extern void FUN_01024744(void);
__attribute__((naked)) void FUN_010247dc(void)
{
    __asm__ volatile(
        "push {r4,r5,r6,lr}\n"
        "ldr r4, =0x21001bd0\n"
        "ldrb r3,[r4,#0x1c]\n"
        "cbnz r3, 9f\n"
        "ldr r0,[r4,#0x20]\n"
        "and r0,r0,#3\n"
        "bl FUN_01024b20\n"
        "cbz r0, 9f\n"
        "mrs r3, primask\n"
        "cpsid i\n"
        "ldrb r2,[r4,#0xd]\n"
        "cbz r2, 1f\n"
        "cbnz r3, 9f\n"
        "cpsie i\n"
        "9:\n"
        "pop {r4,r5,r6,pc}\n"
        "1:\n"
        "movs r2,#1\n"
        "strb r2,[r4,#0xd]\n"
        "cbnz r3, 2f\n"
        "cpsie i\n"
        "2:\n"
        "ldr r5, =0x41005000\n"
        "movs r3,#0\n"
        "movs r6,#0x80\n"
        "str.w r6,[r5,#0x308]\n"
        "str.w r3,[r5,#0x11c]\n"
        "strb.w r3,[r4,#0x24]\n"
        "bl FUN_01024744\n"
        "str.w r6,[r5,#0x304]\n"
        "b 9b\n"
    );
}



