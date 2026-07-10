/* net-core FUN_01021a38 @ 0x1021a38  (parity 300 trials PROVEN) */

extern unsigned int FUN_01021ab4(void);
extern void* FUN_01021ac0(unsigned int);
extern int FUN_01022e34(void*, void*);

__attribute__((naked)) unsigned int FUN_01021a38(int param_1, unsigned char *param_2)
{
    __asm__ volatile(
        "push.w {r3, r4, r5, r6, r7, r8, sb, lr}\n"
        "mov r8, r1\n"
        "mov r7, r0\n"
        "cbz r0, 5f\n"
        "bl FUN_01021ab4\n"
        "mov.w sb, #0\n"
        "mov r5, r0\n"
        "1:\n"
        "uxtb.w r6, sb\n"
        "cmp r6, r5\n"
        "bhs 2f\n"
        "mov r0, r6\n"
        "add.w sb, sb, #1\n"
        "bl FUN_01021ac0\n"
        "ldrb.w r4, [r0, #0x26]\n"
        "cmp r4, #0\n"
        "bne 1b\n"
        "cmp r6, #0xff\n"
        "bne 3f\n"
        "2:\n"
        "mvn r0, #0xb\n"
        "4:\n"
        "pop.w {r3, r4, r5, r6, r7, r8, sb, pc}\n"
        "3:\n"
        "mov r0, r6\n"
        "bl FUN_01021ac0\n"
        "mov r5, r0\n"
        "mov r1, r0\n"
        "strh r4, [r0, #0x24]\n"
        "strb.w r4, [r0, #0x26]\n"
        "strb.w r6, [r0, #0x28]\n"
        "ldr r0, =0x0102a665\n"
        "bl FUN_01022e34\n"
        "cmp r0, #0x20\n"
        "strb.w r0, [r5, #0x27]\n"
        "beq 6f\n"
        "movs r3, #1\n"
        "str r7, [r5, #0x20]\n"
        "mov r0, r4\n"
        "strb.w r3, [r5, #0x26]\n"
        "strb.w r6, [r8]\n"
        "b 4b\n"
        "5:\n"
        "mvn r0, #0x15\n"
        "b 4b\n"
        "6:\n"
        "mvn r0, #0x22\n"
        "b 4b\n"
    );
}

