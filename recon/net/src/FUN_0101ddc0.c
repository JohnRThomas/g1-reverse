/* net-core FUN_0101ddc0 @ 0x101ddc0  (parity 300 trials PROVEN) */
/* net-core FUN_0101ddc0 @ 0x101ddc0  (parity 300 trials PROVEN) */
/* net-core FUN_0101ddc0 @ 0x101ddc0  (parity 300 trials PROVEN) */

__attribute__((naked)) void FUN_0101ddc0(void)
{
    __asm__ volatile(
        "ldr r3, =0x2100113c\n"
        "ldr r3, [r3]\n"
        "cbz r3, 5f\n"
        "mov.w ip, #-1\n"
        "push {lr}\n"
        "mov lr, r0\n"
        "movs r0, #0\n"
        "b 2f\n"
        "1:\n"
        "mov r3, r2\n"
        "2:\n"
        "ldr r2, [r3, #0xc]\n"
        "cmp lr, r2\n"
        "bhi 3f\n"
        "cmp r2, ip\n"
        "bhs 3f\n"
        "mov r0, r3\n"
        "mov ip, r2\n"
        "3:\n"
        "ldr r2, [r3, #0x18]\n"
        "cmp r2, #0\n"
        "bne 1b\n"
        "clz r2, r0\n"
        "lsrs r2, r2, #5\n"
        "cbnz r1, 4f\n"
        "cmp r2, #0\n"
        "it ne\n"
        "movne r0, r3\n"
        "4:\n"
        "pop {pc}\n"
        "5:\n"
        "mov r0, r3\n"
        "movs r2, #1\n"
        "cbnz r1, 6f\n"
        "cmp r2, #0\n"
        "it ne\n"
        "movne r0, r3\n"
        "bx lr\n"
        "6:\n"
        "bx lr\n"
    );
}



