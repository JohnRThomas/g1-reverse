#include "g1_net_symbols.h"
/* net-core FUN_01020088 @ 0x1020088  (parity 300 trials PROVEN) */
/* net-core FUN_01020088 @ 0x1020088  (parity 300 trials PROVEN) */
/* net-core FUN_01020088 @ 0x1020088  (parity 300 trials PROVEN) */

extern void FUN_0101ff4c(void);
extern void FUN_01008d00(int,int);
__attribute__((naked)) void FUN_01020088(void)
{
    __asm__ volatile(
        "push {r4,r5,r6,lr}\n"
        "ldr r5, =0x4100e000\n"
        "movs r6, #0\n"
        "mov r4, r0\n"
        "str.w r6, [r5, #0x500]\n"
        "str.w r6, [r5, #0x500]\n"
        "bl FUN_0101ff4c\n"
        "cmp r4, #1\n"
        "str.w r6, [r5, #0x80]\n"
        "beq 1f\n"
        "cmp r4, #2\n"
        "beq 2f\n"
        "cbz r4, 3f\n"
        "movs r1, #0x82\n"
        "movs r0, #0x3d\n"
        "bl FUN_01008d00\n"
        "1:\n"
        "movs r2, #2\n"
        "ldr r3, =0x210014e4\n"
        "str.w r2, [r5, #0x500]\n"
        "str.w r3, [r5, #0x514]\n"
        "3:\n"
        "pop {r4,r5,r6,pc}\n"
        "2:\n"
        "movs r1, #3\n"
        "ldr r2, =0x210014e4\n"
        "ldr r3, =0x80000003\n"
        "str.w r1, [r5, #0x500]\n"
        "str.w r2, [r5, #0x514]\n"
        "str.w r3, [r5, #0x80]\n"
        "pop {r4,r5,r6,pc}\n"
    );
}



