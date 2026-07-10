/* net-core FUN_010389f8 @ 0x10389f8  (parity 300 trials PROVEN) */

extern int FUN_0103b14a(void);
extern void FUN_01038958(void);

__attribute__((naked)) void FUN_010389f8(void)
{
    __asm__ volatile(
        "push {r3, r4, r5, lr}\n"
        "mov r4, r0\n"
        "mov r5, r1\n"
        "bl FUN_0103b14a\n"
        "cbnz r0, 1f\n"
        "ldr r3, =0x21004b28\n"
        "ldr r3, [r3, #8]\n"
        "ldr.w r3, [r3, #0x84]\n"
        "cbnz r3, 2f\n"
        "pop {r3, r4, r5, pc}\n"
        "1:\n"
        "ldr r3, =0x210008b4\n"
        "2:\n"
        "mov r2, r5\n"
        "mov r1, r4\n"
        "mov r0, r3\n"
        "pop.w {r3, r4, r5, lr}\n"
        "b.w FUN_01038958\n"
    );
}

