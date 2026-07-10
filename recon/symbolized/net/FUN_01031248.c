#include "g1_net_symbols.h"
/* net-core FUN_01031248 @ 0x1031248  (parity 300 trials PROVEN) */

__attribute__((naked)) void FUN_01031248(void)
{
    __asm__ volatile(
        "movs r3,#1\n"
        "lsls r3,r0\n"
        "push {r4,r5,r6,lr}\n"
        "mvns r4,r3\n"
        "ldr r2,=0x2100496c\n"
        "Lb1252:\n"
        "ldaex r1,[r2]\n"
        "and.w r5,r1,r4\n"
        "stlex r6,r5,[r2]\n"
        "cmp r6,#0\n"
        "bne Lb1252\n"
        "mov.w r2,#0x10000\n"
        "lsls r2,r0\n"
        "ldr r0,=0x41016000\n"
        "str.w r2,[r0,#0x308]\n"
        "dmb sy\n"
        "isb sy\n"
        "tst r3,r1\n"
        "ite ne\n"
        "movne r0,#1\n"
        "moveq r0,#0\n"
        "pop {r4,r5,r6,pc}\n"
    );
}

