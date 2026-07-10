#include "g1_net_symbols.h"
/* net-core FUN_01036824 @ 0x1036824  (parity 300 trials PROVEN) */

extern void FUN_0103610c(void);
extern void FUN_01036144(void);
extern void FUN_0103705c(void);
extern void FUN_01037130(void);
extern void FUN_010379d4(void);
extern void FUN_01039bb0(void);
extern void FUN_01039bbe(void);
extern void FUN_0103b4f6(void);

__attribute__((naked)) void FUN_01036824(void)
{
    __asm__ volatile(
        "push {r3, r4, r5, lr}\n"
        "mov r4, r0\n"
        "mov.w r3, #0x40\n"
        "mrs r5, basepri\n"
        "msr basepri_max, r3\n"
        "isb sy\n"
        "ldr r0, =0x21004b4c\n"
        "bl FUN_0103610c\n"
        "cbnz r0, 1f\n"
        "ldr r1, =0x0103d3b6\n"
        "ldr r0, =0x0103d2a7\n"
        "movs r2, #0x72\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0x72\n"
        "ldr r0, =0x0103d3b6\n"
        "bl FUN_01039bb0\n"
        "1:\n"
        "ldr r0, =0x21004b4c\n"
        "bl FUN_01036144\n"
        "mov r0, r4\n"
        "bl FUN_010379d4\n"
        "cbz r0, 2f\n"
        "movs r2, #0\n"
        "str.w r2, [r0, #0x90]\n"
        "bl FUN_0103705c\n"
        "3:\n"
        "mov r1, r5\n"
        "pop.w {r3, r4, r5, lr}\n"
        "ldr r0, =0x21004b4c\n"
        "b.w FUN_01037130\n"
        "2:\n"
        "ldrd r3, r2, [r4, #8]\n"
        "cmp r2, r3\n"
        "it ne\n"
        "addne r3, #1\n"
        "movs r1, #2\n"
        "str r3, [r4, #8]\n"
        "add.w r0, r4, #0x10\n"
        "bl FUN_0103b4f6\n"
        "b 3b\n"
    );
}

