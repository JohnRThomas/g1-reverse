/* net-core FUN_01034b18 @ 0x1034b18  (parity 300 trials PROVEN) */
/* net-core FUN_01034b18 @ 0x1034b18  (parity 300 trials PROVEN) */
/* net-core FUN_01034b18 @ 0x1034b18  (parity 300 trials PROVEN) */
/* net-core FUN_01034b18 @ 0x1034b18  (parity 300 trials PROVEN) */

extern int FUN_010344d4(void);
extern int FUN_01034508(int);
extern unsigned int FUN_01034520(int);
extern void FUN_0103a9be(int,int);
__attribute__((naked)) void FUN_01034b18(void)
{
    __asm__ volatile(
        "push {r4,lr}\n"
        "mov r4,r0\n"
        "bl FUN_010344d4\n"
        "cbz r0, 1f\n"
        "mov r0,r4\n"
        "bl FUN_01034508\n"
        "cbnz r0, 1f\n"
        "mov r0,r4\n"
        "bl FUN_01034520\n"
        "movs r3,#1\n"
        "ldr r2, =0x4100a000\n"
        "lsls r3,r0\n"
        "lsls r0,r0,#2\n"
        "add.w r0,r0,#0x41000000\n"
        "str.w r3,[r2,#0x308]\n"
        "add.w r0,r0,#0xa000\n"
        "ldr.w r3,[r0,#0x510]\n"
        "bic r3,r3,#3\n"
        "str.w r3,[r0,#0x510]\n"
        "pop {r4,pc}\n"
        "1:\n"
        "mov r0,r4\n"
        "pop.w {r4,lr}\n"
        "movs r1,#0\n"
        "b.w FUN_0103a9be\n"
    );
}




