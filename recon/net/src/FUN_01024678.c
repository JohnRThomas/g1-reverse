/* net-core FUN_01024678 @ 0x1024678  (parity 300 trials PROVEN) */
/* net-core FUN_01024678 @ 0x1024678  (parity 300 trials PROVEN) */
/* net-core FUN_01024678 @ 0x1024678  (parity 300 trials PROVEN) */

extern void FUN_010256dc(int,int,int,int,int);
__attribute__((naked)) void FUN_01024678(void)
{
    __asm__ volatile(
        "push {r3,lr}\n"
        "cbz r1, 1f\n"
        "cbz r0, 2f\n"
        "mov.w r3, #-1\n"
        "mov r2, r3\n"
        "umlal r3, r2, r0, r1\n"
        "ldr r1, =0x000f423f\n"
        "cmp r2, r1\n"
        "bls 3f\n"
        "movs r1, #0x71\n"
        "movs r0, #0x6d\n"
        "bl FUN_010256dc\n"
        "3:\n"
        "lsrs r0, r3, #0x14\n"
        "movw r1, #0xf424\n"
        "ubfx r3, r3, #4, #0x10\n"
        "orr.w r0, r0, r2, lsl #12\n"
        "udiv r2, r0, r1\n"
        "add.w r0, r3, r0, lsl #16\n"
        "ldr r3, =0xf4240000\n"
        "mls r0, r3, r2, r0\n"
        "udiv r0, r0, r1\n"
        "orr.w r0, r0, r2, lsl #16\n"
        "adds r0, #1\n"
        "2:\n"
        "pop {r3,pc}\n"
        "1:\n"
        "mov r0, r1\n"
        "b 2b\n"
    );
}



