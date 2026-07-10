/* net-core FUN_0102b900 @ 0x102b900  (parity 300 trials PROVEN) */

extern void FUN_01036198(void);
extern void FUN_01039722(void);

__attribute__((naked)) void FUN_0102b900(void)
{
    __asm__ volatile(
        "push {r0, r1, r2, lr}\n"
        "strb.w r0, [sp, #7]\n"
        "movs r2, #0\n"
        "add.w r1, sp, #7\n"
        "movs r3, #0\n"
        "ldr r0, =0x210008e0\n"
        "bl FUN_01036198\n"
        "mov r1, r0\n"
        "cbz r0, 1f\n"
        "ldr r3, =0x21000580\n"
        "ldr r3, [r3]\n"
        "cmp r3, #0\n"
        "ble 2f\n"
        "ldr r0, =0x0103d23b\n"
        "bl FUN_01039722\n"
        "2:\n"
        "eors r0, r0\n"
        "msr basepri, r0\n"
        "mov.w r0, #3\n"
        "svc #2\n"
        "1:\n"
        "add sp, #0xc\n"
        "ldr pc, [sp], #4\n"
    );
}

