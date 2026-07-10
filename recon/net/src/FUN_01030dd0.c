/* net-core FUN_01030dd0 @ 0x1030dd0  (parity 34 trials PROVEN) */
/* net-core FUN_01030dd0 @ 0x1030dd0  (parity 34 trials PROVEN) */
/* net-core FUN_01030dd0 @ 0x1030dd0  (parity 34 trials PROVEN) */
/* net-core FUN_01030dd0 @ 0x1030dd0  (parity 34 trials PROVEN) */

extern void FUN_01039bbe(int,int,int,int,int);
extern void FUN_01039bb0(int,int);
__attribute__((naked)) void FUN_01030dd0(void)
{
    __asm__ volatile(
        "push {r3,lr}\n"
        "ldr r3,[r0]\n"
        "mov r2,r0\n"
        "lsrs r1,r3,#5\n"
        "beq 5f\n"
        "cmp r1,#1\n"
        "bne 1f\n"
        "movw r1,#0xffff\n"
        "and r3,r3,#0x1f\n"
        "lsrs r1,r3\n"
        "lsls r0,r1,#0x1f\n"
        "bmi 6f\n"
        "1:\n"
        "ldr r1, =0x0103df89\n"
        "ldr r0, =0x0103d2a7\n"
        "movw r2,#0x32f\n"
        "bl FUN_01039bbe\n"
        "movw r1,#0x32f\n"
        "ldr r0, =0x0103df89\n"
        "bl FUN_01039bb0\n"
        "5:\n"
        "mov.w r1,#-1\n"
        "lsrs r1,r3\n"
        "lsls r1,r1,#0x1f\n"
        "bpl 1b\n"
        "ldr r0, =0x418c0500\n"
        "b 7f\n"
        "6:\n"
        "ldr r0, =0x418c0800\n"
        "7:\n"
        "str r3,[r2]\n"
        "pop {r3,pc}\n"
    );
}




