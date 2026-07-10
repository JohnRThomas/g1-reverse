#include "g1_net_symbols.h"
/* net-core FUN_01035fa0 @ 0x1035fa0  (parity 300 trials PROVEN) */

extern void FUN_01035edc(void);
extern void FUN_0103719c(void);
extern void FUN_01037f8c(void);
extern void FUN_01039bb0(void);
extern void FUN_01039bbe(void);

__attribute__((naked)) void FUN_01035fa0(void)
{
    __asm__ volatile(
        "push {r4, r5, r6, r7, lr}\n"
        "sub sp, #0x1c\n"
        "mov r4, r0\n"
        "ldrd r7, r6, [sp, #0x48]\n"
        "mrs r5, ipsr\n"
        "cbz r5, 1f\n"
        "ldr r1, =0x0103ea45\n"
        "ldr r0, =0x0103d2a7\n"
        "mov.w r2, #0x28c\n"
        "bl FUN_01039bbe\n"
        "mov.w r1, #0x28c\n"
        "ldr r0, =0x0103ea45\n"
        "bl FUN_01039bb0\n"
        "1:\n"
        "str r5, [sp, #0x14]\n"
        "ldr r5, [sp, #0x40]\n"
        "str r5, [sp, #0x10]\n"
        "ldr r5, [sp, #0x3c]\n"
        "str r5, [sp, #0xc]\n"
        "ldr r5, [sp, #0x38]\n"
        "str r5, [sp, #8]\n"
        "ldr r5, [sp, #0x34]\n"
        "str r5, [sp, #4]\n"
        "ldr r5, [sp, #0x30]\n"
        "str r5, [sp]\n"
        "bl FUN_01035edc\n"
        "cmp.w r6, #-1\n"
        "it eq\n"
        "cmpeq.w r7, #-1\n"
        "beq 2f\n"
        "orrs.w r3, r6, r7\n"
        "bne 3f\n"
        "mov r0, r4\n"
        "bl FUN_0103719c\n"
        "2:\n"
        "mov r0, r4\n"
        "add sp, #0x1c\n"
        "pop {r4, r5, r6, r7, pc}\n"
        "3:\n"
        "mov r2, r7\n"
        "mov r3, r6\n"
        "ldr r1, =0x0103bac9\n"
        "add.w r0, r4, #0x18\n"
        "bl FUN_01037f8c\n"
        "b 2b\n"
    );
}

