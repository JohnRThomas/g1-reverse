/* net-core FUN_01025034 @ 0x1025034  (parity 300 trials PROVEN) */
/* net-core FUN_01025034 @ 0x1025034  (parity 300 trials PROVEN) */
/* net-core FUN_01025034 @ 0x1025034  (parity 300 trials PROVEN) */
/* net-core FUN_01025034 @ 0x1025034  (parity 300 trials PROVEN) */

extern unsigned int FUN_01024440(unsigned int);
__attribute__((naked)) void FUN_01025034(void)
{
    __asm__ volatile(
        "push {r3,r4,r5,lr}\n"
        "mrs r5, primask\n"
        "cpsid i\n"
        "ldr r2, =0x41011000\n"
        "ldr r1, =0x21001bf8\n"
        "ldr.w r0,[r2,#0x504]\n"
        "ldr.w r3,[r2,#0x104]\n"
        "cbz r3, 1f\n"
        "2:\n"
        "movs r4,#0\n"
        "ldr r3,[r1,#0x10]\n"
        "adds r3,#1\n"
        "str r3,[r1,#0x10]\n"
        "str.w r4,[r2,#0x104]\n"
        "ldr.w r0,[r2,#0x504]\n"
        "ldr.w r3,[r2,#0x104]\n"
        "cmp r3,#0\n"
        "bne 2b\n"
        "1:\n"
        "ldr r4,[r1,#0x10]\n"
        "cbnz r5, 3f\n"
        "cpsie i\n"
        "3:\n"
        "bl FUN_01024440\n"
        "ldr r3, =0x1e848000\n"
        "movs r1,#0\n"
        "umlal r0,r1,r4,r3\n"
        "pop {r3,r4,r5,pc}\n"
    );
}





