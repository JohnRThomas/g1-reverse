/* net-core FUN_0103576c @ 0x103576c  (parity 300 trials PROVEN) */

extern void FUN_010355bc(void);
extern void FUN_01039bb0(void);
extern void FUN_01039bbe(void);
extern void FUN_0103ab0e(void);
extern void FUN_0103aff2(void);

__attribute__((naked)) void FUN_0103576c(void)
{
    __asm__ volatile(
        "push.w {r4, r5, r6, r7, r8, sb, lr}\n"
        "sub sp, #0x14\n"
        "mov r7, r1\n"
        "mov r8, r2\n"
        "add r1, sp, #0xc\n"
        "ldr r2, [sp, #0x34]\n"
        "mov r6, r0\n"
        "mov sb, r3\n"
        "bl FUN_0103aff2\n"
        "mov r4, r0\n"
        "cbz r0, 1f\n"
        "ldr r5, [sp, #0x30]\n"
        "ldr r3, [sp, #0xc]\n"
        "ldr.w r0, [r6, #0xac]\n"
        "cmp r5, r3\n"
        "it ge\n"
        "movge r5, r3\n"
        "ldr r1, [r0]\n"
        "ldr.w ip, [r0, #8]\n"
        "subs r1, r4, r1\n"
        "cmp r1, ip\n"
        "it hs\n"
        "movhs.w r1, #-1\n"
        "mov r3, r5\n"
        "mov r2, sb\n"
        "bl FUN_0103ab0e\n"
        "cmp r5, r0\n"
        "beq 2f\n"
        "ldr r1, =0x0103e889\n"
        "ldr r0, =0x0103d2a7\n"
        "movw r2, #0x207\n"
        "bl FUN_01039bbe\n"
        "movw r1, #0x207\n"
        "ldr r0, =0x0103e889\n"
        "bl FUN_01039bb0\n"
        "2:\n"
        "mov r3, r4\n"
        "mov r2, r8\n"
        "mov r1, r7\n"
        "mov r0, r6\n"
        "str r5, [sp]\n"
        "bl FUN_010355bc\n"
        "3:\n"
        "add sp, #0x14\n"
        "pop.w {r4, r5, r6, r7, r8, sb, pc}\n"
        "1:\n"
        "ldr r0, =0xfffff82e\n"
        "b 3b\n"
    );
}

