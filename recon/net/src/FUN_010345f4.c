/* net-core FUN_010345f4 @ 0x10345f4  (parity 300 trials PROVEN) */

extern int FUN_0103a8ea(unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);

__attribute__((naked)) unsigned int FUN_010345f4(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    __asm__ volatile(
        "push {r3, lr}\n"
        "ldr r2, [r0]\n"
        "mov r1, r0\n"
        "mov r0, r2\n"
        "bl FUN_0103a8ea\n"
        "cbnz r0, .Lafter\n"
        "ldr r1, =0x0103df89\n"
        "movw r2, #0x32f\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movw r1, #0x32f\n"
        ".Lloopcall:\n"
        "ldr r0, =0x0103df89\n"
        "bl FUN_01039bb0\n"
        ".Lafter:\n"
        "and r3, r2, #0x1f\n"
        "lsrs r2, r2, #5\n"
        "str r3, [r1]\n"
        "beq .Lret0\n"
        "cmp r2, #1\n"
        "beq .Lret1\n"
        "ldr r1, =0x0103df89\n"
        "mov.w r2, #0x338\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "mov.w r1, #0x338\n"
        "b .Lloopcall\n"
        ".Lret0:\n"
        "ldr r0, =0x418c0500\n"
        "pop {r3, pc}\n"
        ".Lret1:\n"
        "ldr r0, =0x418c0800\n"
        "b .Lret0\n"
    );
}

