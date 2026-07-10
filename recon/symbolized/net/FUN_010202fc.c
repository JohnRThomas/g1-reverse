#include "g1_net_symbols.h"
/* net-core FUN_010202fc @ 0x10202fc  (parity 300 trials PROVEN) */
/* net-core FUN_010202fc @ 0x10202fc  (parity 300 trials PROVEN) */
/* net-core FUN_010202fc @ 0x10202fc  (parity 300 trials PROVEN) */

extern void FUN_01008d00(int,int,int,int,int);
__attribute__((naked)) void FUN_010202fc(void)
{
    __asm__ volatile(
        "push {r3,lr}\n"
        "subs r1, #1\n"
        "ldr r3, =0x210015f0\n"
        "strb.w r0, [r3,#0x34]\n"
        "cmp r1, #7\n"
        "bhi 9f\n"
        "tbb [pc, r1]\n"
        ".byte 0x15,0x13,0x17,0x04,0x17,0x17,0x17,0x04\n"
        ".align 1\n"
        "7:\n"
        "ldr r1, =0x63900108\n"
        "8:\n"
        "ldr r2, =0x02030000\n"
        "ldr r3, =0x41008000\n"
        "orrs r2, r0\n"
        "str.w r1, [r3, #0x514]\n"
        "str.w r2, [r3, #0x518]\n"
        "ldr.w r3, [r3, #0x550]\n"
        "and r3, r3, #0xf7\n"
        "cmp r3, #3\n"
        "beq 6f\n"
        "pop {r3,pc}\n"
        "4:\n"
        "ldr r1, =0x01100108\n"
        "b 8b\n"
        "3:\n"
        "ldr r1, =0x00100108\n"
        "b 8b\n"
        "9:\n"
        "mov.w r1, #0x2dc\n"
        "movs r0, #0x3e\n"
        "bl FUN_01008d00\n"
        "6:\n"
        "mov.w r1, #0x2f4\n"
        "movs r0, #0x3e\n"
        "bl FUN_01008d00\n"
    );
}



