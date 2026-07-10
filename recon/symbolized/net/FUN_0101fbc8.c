#include "g1_net_symbols.h"
/* net-core FUN_0101fbc8 @ 0x101fbc8  (parity 300 trials PROVEN) */
/* net-core FUN_0101fbc8 @ 0x101fbc8  (parity 300 trials PROVEN) */
/* net-core FUN_0101fbc8 @ 0x101fbc8  (parity 300 trials PROVEN) */
/* net-core FUN_0101fbc8 @ 0x101fbc8  (parity 300 trials PROVEN) */

extern void FUN_01008d00(int,int);
extern int FUN_01009d18(int,int);
extern void FUN_01009d64(int,int);
__attribute__((naked)) void FUN_0101fbc8(void)
{
    __asm__ volatile(
        "push {r4,r5,r6,lr}\n"
        "ldr r5, =0x2100052c\n"
        "mov r4, r1\n"
        "movs r1, #6\n"
        "bl FUN_01009d64\n"
        "ldr r3,[r5]\n"
        "cbz r3, 9f\n"
        "ldrb.w r3,[r4,#0x38]\n"
        "cbz r3, 9f\n"
        "ldr r3, =0x21000528\n"
        "ldr r3,[r3]\n"
        "cbnz r3, 2f\n"
        "movw r1,#0x245\n"
        "movs r0,#0xd\n"
        "bl FUN_01008d00\n"
        "2:\n"
        "blx r3\n"
        "movs r1,#9\n"
        "uxth r0,r0\n"
        "bl FUN_01009d18\n"
        "cbnz r0, 3f\n"
        "mov.w r1,#0x248\n"
        "movs r0,#0xd\n"
        "bl FUN_01008d00\n"
        "b 2b\n"
        "3:\n"
        "ldr r3,[r5]\n"
        "movs r1,#0x3e\n"
        "pop.w {r4,r5,r6,lr}\n"
        "bx r3\n"
        "9:\n"
        "pop {r4,r5,r6,pc}\n"
    );
}




