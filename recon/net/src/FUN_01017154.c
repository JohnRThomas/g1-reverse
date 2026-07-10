/* net-core FUN_01017154 @ 0x1017154  (parity 300 trials PROVEN) */

extern void FUN_0100aa3c(void);
extern void FUN_0100d760(void);
extern void FUN_0101709c(void);
extern void FUN_0101a070(void);
extern void FUN_010295d6(void);

__attribute__((naked)) void FUN_01017154(void)
{
    __asm__ volatile(
        "push {r4, lr}\n"
        "mov r4, r0\n"
        "sub sp, #0x28\n"
        "bl FUN_0100d760\n"
        "ldr r2, =0x2100001c\n"
        "ldrb r3, [r4]\n"
        "strb r0, [r2]\n"
        "and r3, r3, #0xf\n"
        "cmp r3, #7\n"
        "beq 1f\n"
        "2:\n"
        "movs r0, #1\n"
        "add sp, #0x28\n"
        "pop {r4, pc}\n"
        "1:\n"
        "mov r0, r4\n"
        "mov r1, sp\n"
        "bl FUN_0101a070\n"
        "movs r2, #0\n"
        "ldrb.w r3, [sp]\n"
        "str r2, [sp, #8]\n"
        "cmp r3, #0\n"
        "bne 2b\n"
        "ldrb.w r3, [sp, #1]\n"
        "lsls r3, r3, #0x1f\n"
        "bpl 2b\n"
        "ldr r4, =0x21000f90\n"
        "ldr r1, [sp, #4]\n"
        "ldrb.w r0, [sp, #0x11]\n"
        "add.w r3, r4, #0x89\n"
        "ldrb.w r2, [r4, #0x90]\n"
        "bl FUN_0100aa3c\n"
        "cmp r0, #0\n"
        "beq 2b\n"
        "movs r1, #1\n"
        "add.w r0, r4, #0x84\n"
        "bl FUN_010295d6\n"
        "movs r1, #0xff\n"
        "mov r0, sp\n"
        "bl FUN_0101709c\n"
        "cmp r0, #0\n"
        "beq 2b\n"
        "movs r0, #3\n"
        "b 3f\n"
        "3:\n"
        "add sp, #0x28\n"
        "pop {r4, pc}\n"
    );
}

