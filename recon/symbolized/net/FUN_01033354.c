#include "g1_net_symbols.h"
/* net-core FUN_01033354 @ 0x1033354  (parity 300 trials PROVEN) */
/* net-core FUN_01033354 @ 0x1033354  (parity 300 trials PROVEN) */
/* net-core FUN_01033354 @ 0x1033354  (parity 300 trials PROVEN) */

extern void FUN_01033ee4(void);
extern void FUN_01032908(void);
extern void FUN_01035068(int);
extern void FUN_01033f38(void);
extern unsigned long long FUN_010327a0(int,int);
extern void FUN_0103b62e(int,int,int);
extern void FUN_0103a83e(void);
__attribute__((naked)) void FUN_01033354(void)
{
    __asm__ volatile(
        "push {r4,lr}\n"
        "movs r4,#0\n"
        "bl FUN_01033ee4\n"
        "bl FUN_01032908\n"
        "ldr r0, =0x21000698\n"
        "bl FUN_01035068\n"
        "bl FUN_01033f38\n"
        "ldr r2, =0x41008000\n"
        "mov r1,r4\n"
        "ldr.w r3,[r2,#0x650]\n"
        "ldr r0, =0x21004b7c\n"
        "and r3,r3,#0x300\n"
        "str.w r3,[r2,#0x650]\n"
        "ldr r3, =0x21006458\n"
        "strb r4,[r3]\n"
        "ldr r3, =0x21006459\n"
        "strb r4,[r3]\n"
        "bl FUN_010327a0\n"
        "movs r2,#0x20\n"
        "bl FUN_0103b62e\n"
        "ldr r3, =0x21006256\n"
        "str r4,[r3]\n"
        "str r4,[r3,#4]\n"
        "pop.w {r4,lr}\n"
        "b.w FUN_0103a83e\n"
    );
}



