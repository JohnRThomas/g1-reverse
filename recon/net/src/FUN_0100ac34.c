/* net-core FUN_0100ac34 @ 0x100ac34  (parity 300 trials PROVEN) */
/* net-core FUN_0100ac34 @ 0x100ac34  (parity 300 trials PROVEN) */
/* net-core FUN_0100ac34 @ 0x100ac34  (parity 300 trials PROVEN) */
/* net-core FUN_0100ac34 @ 0x100ac34  (parity 300 trials PROVEN) */

extern void FUN_01020500(void);
extern void FUN_0101ff4c(void);
extern void FUN_0100efc8(int,int,int);
__attribute__((naked)) void FUN_0100ac34(void)
{
    __asm__ volatile(
        "push {r4,lr}\n"
        "ldr r4, =0x21000c48\n"
        "bl FUN_01020500\n"
        "bl FUN_0101ff4c\n"
        "movs r1, #0\n"
        "ldr r3, [r4, #0x34]\n"
        "ldrh r0, [r4, #0x30]\n"
        "blx r3\n"
        "ldrb r3, [r4, #0x18]\n"
        "cbnz r3, 1f\n"
        "2:\n"
        "ldr r3, [r4, #0x40]\n"
        "ldrb.w r1, [r4, #0x3d]\n"
        "ldrb.w r0, [r4, #0x3e]\n"
        "blx r3\n"
        "movs r3, #0\n"
        "strb.w r3, [r4, #0x44]\n"
        "pop {r4,pc}\n"
        "1:\n"
        "ldm.w r4, {r0,r1,r2}\n"
        "add.w r3, r4, #0xc\n"
        "stm.w r3, {r0,r1,r2}\n"
        "movs r2, #2\n"
        "ldr r1, =0x0100b381\n"
        "add.w r0, r4, #0x19\n"
        "bl FUN_0100efc8\n"
        "b 2b\n"
    );
}




