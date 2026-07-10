/* net-core FUN_01036f74 @ 0x1036f74  (parity 300 trials PROVEN) */
/* net-core FUN_01036f74 @ 0x1036f74  (parity 300 trials PROVEN) */
/* net-core FUN_01036f74 @ 0x1036f74  (parity 300 trials PROVEN) */

extern void FUN_01036f24(int);
extern void FUN_01039bbe(int,int,int,int,int);
extern void FUN_01039bb0(int,int);
__attribute__((naked)) void FUN_01036f74(void)
{
    __asm__ volatile(
        "push {r3,r4,r5,lr}\n"
        "ldr r5, =0x21004b28\n"
        "mov r3, r5\n"
        "ldr r4, [r3, #0x18]!\n"
        "cmp r4, r3\n"
        "beq 1f\n"
        "cbnz r4, 2f\n"
        "1:\n"
        "ldr r4, [r5, #0xc]\n"
        "2:\n"
        "ldr r3, [r5, #8]\n"
        "cbnz r0, 3f\n"
        "cbnz r3, 4f\n"
        "ldr r1, =0x0103eb0e\n"
        "ldr r0, =0x0103d2a7\n"
        "movs r2, #0x8f\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0x8f\n"
        "ldr r0, =0x0103eb0e\n"
        "bl FUN_01039bb0\n"
        "4:\n"
        "ldrb r2, [r3, #0xd]\n"
        "lsls r2, r2, #0x1b\n"
        "bne 3f\n"
        "ldr r2, [r4, #0x18]\n"
        "cbnz r2, 3f\n"
        "ldrh r2, [r3, #0xe]\n"
        "cmp r2, #0x7f\n"
        "bhi 6f\n"
        "3:\n"
        "cmp r4, r3\n"
        "beq 5f\n"
        "mov r0, r4\n"
        "bl FUN_01036f24\n"
        "5:\n"
        "mov r3, r4\n"
        "6:\n"
        "str r3, [r5, #0x14]\n"
        "pop {r3,r4,r5,pc}\n"
    );
}



