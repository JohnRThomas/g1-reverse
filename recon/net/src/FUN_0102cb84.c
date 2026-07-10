/* net-core FUN_0102cb84 @ 0x102cb84  (parity 300 trials PROVEN) */
/* net-core FUN_0102cb84 @ 0x102cb84  (parity 300 trials PROVEN) */
/* net-core FUN_0102cb84 @ 0x102cb84  (parity 300 trials PROVEN) */

extern void FUN_010388c8(void);
extern void FUN_01039bbe(int,int,int,int,int);
extern void FUN_01039bb0(int,int);
__attribute__((naked)) void FUN_0102cb84(void)
{
    __asm__ volatile(
        "push {r3,lr}\n"
        "ldr r2,[r0,#4]\n"
        "mov r3,r0\n"
        "and r2,r2,#3\n"
        "cmp r2,#2\n"
        "str r1,[r0,#8]\n"
        "beq 1f\n"
        "cmp r2,#3\n"
        "mov.w r1,#0\n"
        "beq 2f\n"
        "cmp r2,#1\n"
        "bne 3f\n"
        "str r1,[r3,#4]\n"
        "b 4f\n"
        "2:\n"
        "ldr r0,[r3]\n"
        "str r1,[r3,#4]\n"
        "6:\n"
        "pop {r3,pc}\n"
        "1:\n"
        "ldr r0,[r3]\n"
        "movs r2,#0\n"
        "str r2,[r3,#4]\n"
        "cbnz r0, 5f\n"
        "4:\n"
        "movs r0,#0\n"
        "b 6b\n"
        "3:\n"
        "ldr r1, =0x0103d3e3\n"
        "ldr r0, =0x0103d2a7\n"
        "movs r2,#0x45\n"
        "bl FUN_01039bbe\n"
        "movs r1,#0x45\n"
        "ldr r0, =0x0103d3e3\n"
        "bl FUN_01039bb0\n"
        "5:\n"
        "bl FUN_010388c8\n"
        "b 4b\n"
    );
}



