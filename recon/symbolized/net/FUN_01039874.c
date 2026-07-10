#include "g1_net_symbols.h"
/* net-core FUN_01039874 @ 0x1039874  (parity 300 trials PROVEN) */

extern void FUN_0103973c(void);
extern void FUN_01039768(void);
extern void FUN_010397d2(void);
extern void FUN_010397ea(void);

__attribute__((naked)) void FUN_01039874(void)
{
    __asm__ volatile(
        "push.w {r4, r5, r6, r7, r8, sb, sl, lr}\n"
        "mov r5, r0\n"
        "ldr r0, [r0, #8]\n"
        "mov r8, r1\n"
        "bl FUN_010397d2\n"
        "add.w sl, r5, r0, lsl #2\n"
        "ldr.w sb, [sl, #0x10]\n"
        "mov r6, r0\n"
        "cmp.w sb, #0\n"
        "beq 1f\n"
        "movs r7, #3\n"
        "2:\n"
        "ldr.w r4, [sl, #0x10]\n"
        "mov r0, r5\n"
        "mov r1, r4\n"
        "bl FUN_01039768\n"
        "cmp r0, r8\n"
        "blo 3f\n"
        "mov r2, r6\n"
        "mov r1, r4\n"
        "mov r0, r5\n"
        "bl FUN_010397ea\n"
        "mov r0, r4\n"
        "pop.w {r4, r5, r6, r7, r8, sb, sl, pc}\n"
        "3:\n"
        "movs r2, #3\n"
        "mov r1, r4\n"
        "mov r0, r5\n"
        "bl FUN_0103973c\n"
        "subs r7, #1\n"
        "str.w r0, [sl, #0x10]\n"
        "beq 1f\n"
        "cmp sb, r0\n"
        "bne 2b\n"
        "1:\n"
        "mov.w r4, #-1\n"
        "ldr r3, [r5, #0xc]\n"
        "adds r6, #1\n"
        "lsls r4, r6\n"
        "ands r4, r3\n"
        "beq 4f\n"
        "rbit r2, r4\n"
        "clz r2, r2\n"
        "adds r3, r2, #4\n"
        "ldr.w r4, [r5, r3, lsl #2]\n"
        "mov r2, r6\n"
        "mov r1, r4\n"
        "mov r0, r5\n"
        "bl FUN_010397ea\n"
        "4:\n"
        "mov r0, r4\n"
        "pop.w {r4, r5, r6, r7, r8, sb, sl, pc}\n"
    );
}

