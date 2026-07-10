/* net-core FUN_0102d1c0 @ 0x102d1c0  (parity 300 trials PROVEN) */
/* net-core FUN_0102d1c0 @ 0x102d1c0  (parity 300 trials PROVEN) */

extern void FUN_0103a6c6(void);

__attribute__((naked)) void FUN_0102d1c0(void)
{
    __asm__ volatile(
        "push {r3, r4, r5, r6, r7, lr}\n"
        "ldr r1, =0x21004fab\n"
        "movs r3, #0\n"
        "strexb r2, r3, [r1]\n"
        "cbnz r2, 5f\n"
        "ldr r3, =0x21004faa\n"
        "ldrb r5, [r3]\n"
        "cbz r5, 5f\n"
        "movs r3, #5\n"
        "ldr r6, =0x21004fa8\n"
        "ldr r7, =0x21004640\n"
        "ldrb r4, [r6]\n"
        "adds r4, #1\n"
        "udiv r3, r4, r3\n"
        "add.w r3, r3, r3, lsl #2\n"
        "subs r4, r4, r3\n"
        "bl FUN_0103a6c6\n"
        "ldr r2, =0x21004fa7\n"
        "ldrb r3, [r2]\n"
        "cbz r3, 1f\n"
        "ldr.w r3, [r7, r4, lsl #2]\n"
        "subs r0, r0, r3\n"
        "cmp r0, #7\n"
        "bls 5f\n"
        "1:\n"
        "ldr r3, =0x41005000\n"
        "ldr.w r1, [r3, #0x114]\n"
        "cbz r1, 2f\n"
        "movs r1, #0\n"
        "str.w r1, [r3, #0x114]\n"
        "ldr.w r3, [r3, #0x114]\n"
        "strb r4, [r6]\n"
        "cbnz r4, 2f\n"
        "movs r3, #1\n"
        "strb r3, [r2]\n"
        "2:\n"
        "ldrb r4, [r6]\n"
        "bl FUN_0103a6c6\n"
        "str.w r0, [r7, r4, lsl #2]\n"
        "4:\n"
        "mov r0, r5\n"
        "pop {r3, r4, r5, r6, r7, pc}\n"
        "5:\n"
        "ldr r2, =0x41012000\n"
        "movs r5, #0\n"
        "ldr.w r3, [r2, #0x1ac]\n"
        "bic r3, r3, #0x80000000\n"
        "str.w r3, [r2, #0x1ac]\n"
        "movs r2, #1\n"
        "ldr r3, =0x4100b000\n"
        "str r2, [r3, #4]\n"
        "b 4b\n"
    );
}


