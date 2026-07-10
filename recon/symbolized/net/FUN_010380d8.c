#include "g1_net_symbols.h"
/* net-core FUN_010380d8 @ 0x10380d8  (parity 300 trials PROVEN) */

extern void FUN_0103610c(void);
extern void FUN_01036144(void);
extern void FUN_01036128(void);
extern void FUN_01037f54(void);
extern void FUN_01039bb0(void);
extern void FUN_01039bbe(void);

__attribute__((naked)) void FUN_010380d8(void)
{
    __asm__ volatile(
        "push {r3, r4, r5, lr}\n"
        "mov r4, r0\n"
        "mov.w r3, #0x40\n"
        "mrs r5, basepri\n"
        "msr basepri_max, r3\n"
        "isb sy\n"
        "ldr r0, =0x21004b70\n"
        "bl FUN_0103610c\n"
        "cbnz r0, 1f\n"
        "ldr r1, =0x0103d3b6\n"
        "movs r2, #0x72\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0x72\n"
        "b 3f\n"
        "1:\n"
        "ldr r0, =0x21004b70\n"
        "bl FUN_01036144\n"
        "ldr r3, [r4]\n"
        "cbz r3, 4f\n"
        "mov r0, r4\n"
        "bl FUN_01037f54\n"
        "movs r4, #0\n"
        "2:\n"
        "ldr r0, =0x21004b70\n"
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
        "mvn r4, #0x15\n"
        "b 2b\n"
        "5:\n"
        "msr basepri, r5\n"
        "isb sy\n"
        "mov r0, r4\n"
        "pop {r3, r4, r5, pc}\n"
    );
}

