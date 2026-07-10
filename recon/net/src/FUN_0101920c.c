/* net-core FUN_0101920c @ 0x101920c  (parity 300 trials PROVEN) */

extern void FUN_01008d00(void);
extern void FUN_010196e0(void);

__attribute__((naked)) void FUN_0101920c(int param_1, int param_2)
{
    __asm__ volatile(
        "push {r4, lr}\n"
        "ldr r4, =0x21000f90\n"
        "ldrb.w r3, [r4, #0x70]\n"
        "cmp r3, #3\n"
        "bne Lassert3\n"
        "subs r0, #2\n"
        "cmp r0, #1\n"
        "bhi Lassert2\n"
        "cbnz r1, Lcall1\n"
        "Lret:\n"
        "movs r3, #0\n"
        "ldr r2, =0x2100104a\n"
        "strh.w r3, [r4, #0xba]\n"
        "strb.w r3, [r4, #0x70]\n"
        "strb r3, [r2, #2]\n"
        "pop {r4, pc}\n"
        "Lcall1:\n"
        "bl FUN_010196e0\n"
        "b Lret\n"
        "Lassert2:\n"
        "movw r1, #0xc52\n"
        "movs r0, #0x32\n"
        "bl FUN_01008d00\n"
        "Lassert3:\n"
        "movw r1, #0xc44\n"
        "movs r0, #0x32\n"
        "bl FUN_01008d00\n"
    );
}

