#include "g1_net_symbols.h"
/* net-core FUN_0103719c @ 0x103719c  (parity 300 trials PROVEN) */

extern void FUN_0103610c(void);
extern void FUN_01036128(void);
extern void FUN_01036144(void);
extern void FUN_01036fcc(void);
extern void FUN_01037130(void);
extern void FUN_01039bb0(void);
extern void FUN_01039bbe(void);

__attribute__((naked)) void FUN_0103719c(void)
{
    __asm__ volatile(
        "push {r3, r4, r5, lr}\n"
        "mov r4, r0\n"
        "mov.w r3, #0x40\n"
        "mrs r5, basepri\n"
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
        "ldr r0, =0x0103d3b6\n"
        "bl FUN_01039bb0\n"
        "1:\n"
        "ldr r0, =0x21004b68\n"
        "bl FUN_01036144\n"
        "ldrb r3, [r4, #0xd]\n"
        "lsls r2, r3, #0x1d\n"
        "bmi 4f\n"
        "ldr r0, =0x21004b68\n"
        "bl FUN_01036128\n"
        "cbnz r0, 2f\n"
        "ldr r1, =0x0103d3b6\n"
        "movs r2, #0xf0\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0xf0\n"
        "b 3f\n"
        "2:\n"
        "msr basepri, r5\n"
        "isb sy\n"
        "pop {r3, r4, r5, pc}\n"
        "4:\n"
        "bic r3, r3, #4\n"
        "mov r0, r4\n"
        "strb r3, [r4, #0xd]\n"
        "bl FUN_01036fcc\n"
        "mov r1, r5\n"
        "pop.w {r3, r4, r5, lr}\n"
        "ldr r0, =0x21004b68\n"
        "b.w FUN_01037130\n"
        "3:\n"
        "ldr r0, =0x0103d3b6\n"
        "bl FUN_01039bb0\n"
    );
}

