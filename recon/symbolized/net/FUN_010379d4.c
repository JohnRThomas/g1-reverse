#include "g1_net_symbols.h"
/* net-core FUN_010379d4 @ 0x10379d4  (parity 300 trials PROVEN) */

extern void FUN_0103610c(void);
extern void FUN_01036128(void);
extern void FUN_01036144(void);
extern void FUN_01037814(void);
extern void FUN_010380d8(void);
extern void FUN_01039bb0(void);
extern void FUN_01039bbe(void);

__attribute__((naked)) void FUN_010379d4(void)
{
    __asm__ volatile(
        "push {r4, r5, r6, lr}\n"
        "mov r5, r0\n"
        "mov.w r3, #0x40\n"
        "mrs r6, basepri\n"
        "msr basepri_max, r3\n"
        "isb sy\n"
        "ldr r0, =0x21004b68\n"
        "bl FUN_0103610c\n"
        "cbnz r0, 1f\n"
        "ldr r1, =0x0103d3b6\n"
        "movs r2, #0x72\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0x72\n"
        "b 3f\n"
        "1:\n"
        "ldr r0, =0x21004b68\n"
        "bl FUN_01036144\n"
        "ldr r4, [r5]\n"
        "cmp r5, r4\n"
        "beq 4f\n"
        "cbz r4, 2f\n"
        "mov r0, r4\n"
        "bl FUN_01037814\n"
        "add.w r0, r4, #0x18\n"
        "bl FUN_010380d8\n"
        "2:\n"
        "ldr r0, =0x21004b68\n"
        "bl FUN_01036128\n"
        "cbnz r0, 5f\n"
        "ldr r1, =0x0103d3b6\n"
        "movs r2, #0xf0\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0xf0\n"
        "3:\n"
        "ldr r0, =0x0103d3b6\n"
        "bl FUN_01039bb0\n"
        "4:\n"
        "movs r4, #0\n"
        "b 2b\n"
        "5:\n"
        "msr basepri, r6\n"
        "isb sy\n"
        "mov r0, r4\n"
        "pop {r4, r5, r6, pc}\n"
    );
}

