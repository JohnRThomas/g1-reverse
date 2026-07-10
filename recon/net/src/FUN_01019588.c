/* net-core FUN_01019588 @ 0x1019588  (parity 300 trials PROVEN) */

extern void FUN_0100a5a0(void);
extern void FUN_0102714a(void);
extern void FUN_010270d2(void);

__attribute__((naked)) void FUN_01019588(void)
{
    __asm__ volatile(
        "push {lr}\n"
        "sub sp, #0xc\n"
        "bl FUN_0100a5a0\n"
        "add.w r2, sp, #2\n"
        "add r1, sp, #4\n"
        "bl FUN_0102714a\n"
        "ldr r0, [sp, #4]\n"
        "bl FUN_010270d2\n"
        "movs r3, #0\n"
        "movs r1, #0xff\n"
        "mov.w ip, #1\n"
        "str.w r3, [r0, #0x1a]\n"
        "mov.w lr, #0x7f\n"
        "str.w r3, [r0, #0x12]\n"
        "str.w r3, [r0, #0x1e]\n"
        "str.w r3, [r0, #0x22]\n"
        "strb.w r1, [r0, #0x20]\n"
        "strb r1, [r0, #0x13]\n"
        "strb.w r1, [r0, #0x25]\n"
        "ldrb r1, [r0, #0x1c]\n"
        "ldr r2, =0x21001058\n"
        "bfi r1, ip, #5, #2\n"
        "str.w r3, [r0, #0x2a]\n"
        "str.w r3, [r0, #0x16]\n"
        "strb.w lr, [r0, #0x2c]\n"
        "str.w r3, [r0, #0x26]\n"
        "str r3, [r2, #0x40]\n"
        "strh.w r3, [r2, #0x44]\n"
        "strb r3, [r2]\n"
        "strb.w r3, [r2, #0x46]\n"
        "strb r1, [r0, #0x1c]\n"
        "add sp, #0xc\n"
        "pop {pc}\n"
    );
}

