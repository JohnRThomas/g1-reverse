/* net-core FUN_0103afac @ 0x103afac  (parity 300 trials PROVEN) */
/* net-core FUN_0103afac @ 0x103afac  (parity 300 trials PROVEN) */
/* net-core FUN_0103afac @ 0x103afac  (parity 300 trials PROVEN) */

extern void FUN_0103aec6(int);
extern int FUN_0103ac46(int,int);
extern void FUN_010353ec(int,int,int);
extern void FUN_0103acca(int);
extern void FUN_0103aec2(int);
__attribute__((naked)) void FUN_0103afac(void)
{
    __asm__ volatile(
        "push {r4,r5,r6,lr}\n"
        "mov r4,r0\n"
        "ldr r5,[r1,#-8]\n"
        "add.w r6,r0,#0x58\n"
        "mov r0,r6\n"
        "uxth r5,r5\n"
        "bl FUN_0103aec6\n"
        "mov r1,r5\n"
        "ldr.w r0,[r4,#0xa4]\n"
        "bl FUN_0103ac46\n"
        "ldr.w r3,[r4,#0xa0]\n"
        "mov r2,r0\n"
        "ldr r3,[r3,#0x18]\n"
        "cmp r3,#1\n"
        "bne 1f\n"
        "mov r1,r5\n"
        "ldr.w r0,[r4,#0xa4]\n"
        "bl FUN_010353ec\n"
        "1:\n"
        "ldr.w r0,[r4,#0xa4]\n"
        "bl FUN_0103acca\n"
        "mov r0,r6\n"
        "pop.w {r4,r5,r6,lr}\n"
        "b.w FUN_0103aec2\n"
    );
}



