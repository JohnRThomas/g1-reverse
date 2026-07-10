/* net-core FUN_0100cb70 @ 0x100cb70  (parity 300 trials PROVEN) */
/* net-core FUN_0100cb70 @ 0x100cb70  (parity 300 trials PROVEN) */
/* net-core FUN_0100cb70 @ 0x100cb70  (parity 300 trials PROVEN) */
/* net-core FUN_0100cb70 @ 0x100cb70  (parity 300 trials PROVEN) */

extern void FUN_0100ab14(int,int,int,int,int);
__attribute__((naked)) void FUN_0100cb70(void)
{
    __asm__ volatile(
        "push {r3,r4,r5,r6,r7,lr}\n"
        "ldr r5, =0x21000d18\n"
        "ldrb r6, [r5,#1]\n"
        "cbz r6, 9f\n"
        "movs r4, #0\n"
        "mov r7, r0\n"
        "1:\n"
        "mov r3, r4\n"
        "adds r1, r5, r3\n"
        "ldrb.w r1, [r1,#0x142]\n"
        "cbz r1, 2f\n"
        "adds r4, #1\n"
        "uxtb r3, r4\n"
        "cmp r3, r6\n"
        "blo 1b\n"
        "9:\n"
        "pop {r3,r4,r5,r6,r7,pc}\n"
        "2:\n"
        "add.w r1, r3, r3, lsl #1\n"
        "adds r4, #1\n"
        "add.w r3, r5, r3, lsl #4\n"
        "mov r2, r7\n"
        "add.w r1, r5, r1, lsl #1\n"
        "add.w r0, r3, #0x82\n"
        "add.w r1, r1, #0x10a\n"
        "bl FUN_0100ab14\n"
        "ldrb r6, [r5,#1]\n"
        "uxtb r3, r4\n"
        "cmp r3, r6\n"
        "blo 1b\n"
        "pop {r3,r4,r5,r6,r7,pc}\n"
    );
}




