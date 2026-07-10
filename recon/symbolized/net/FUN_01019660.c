#include "g1_net_symbols.h"
/* net-core FUN_01019660 @ 0x1019660  (parity 300 trials PROVEN) */

extern void FUN_01008d00(void);
extern void FUN_0100a5a0(void);
extern void FUN_0100a5b4(void);
extern void FUN_0100ef88(void);
extern void FUN_01026d3e(void);
extern void FUN_01026f32(void);
extern void FUN_010270d2(void);
extern void FUN_0102714a(void);

__attribute__((naked)) void FUN_01019660(void)
{
    __asm__ volatile(
        "push {r4, r5, r6, lr}\n"
        "sub sp, #8\n"
        "bl FUN_0100a5a0\n"
        "mov r4, r0\n"
        "add.w r2, sp, #2\n"
        "add r1, sp, #4\n"
        "bl FUN_0102714a\n"
        "ldr r0, [sp, #4]\n"
        "bl FUN_010270d2\n"
        "ldrb r6, [r0, #0x1f]\n"
        "cbnz r6, 1f\n"
        "mov r5, r0\n"
        "mov r0, r4\n"
        "bl FUN_01026d3e\n"
        "cmp r0, #1\n"
        "beq 2f\n"
        "bl FUN_0100a5b4\n"
        "movs r2, #1\n"
        "uxth r1, r0\n"
        "mov r0, r4\n"
        "bl FUN_01026f32\n"
        "cbz r0, 5f\n"
        "mov r0, r4\n"
        "bl FUN_01026d3e\n"
        "cbz r0, 4f\n"
        "movs r2, #6\n"
        "ldr r1, =0x01019a9d\n"
        "mov r0, r5\n"
        "strb r6, [r5, #8]\n"
        "bl FUN_0100ef88\n"
        "3:\n"
        "ldr r3, =0x21001058\n"
        "movs r2, #0\n"
        "strh.w r2, [r3, #0x44]\n"
        "2:\n"
        "add sp, #8\n"
        "pop {r4, r5, r6, pc}\n"
        "1:\n"
        "mov r0, r4\n"
        "bl FUN_01026d3e\n"
        "cmp r0, #0\n"
        "bne 3b\n"
        "4:\n"
        "movw r1, #0x2be\n"
        "movs r0, #0x33\n"
        "bl FUN_01008d00\n"
        "5:\n"
        "movw r1, #0x2ba\n"
        "movs r0, #0x33\n"
        "bl FUN_01008d00\n"
    );
}

