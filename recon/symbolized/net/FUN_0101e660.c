#include "g1_net_symbols.h"
/* net-core FUN_0101e660 @ 0x101e660  (parity 300 trials PROVEN) */
/* net-core FUN_0101e660 @ 0x101e660  (parity 300 trials PROVEN) */
/* net-core FUN_0101e660 @ 0x101e660  (parity 300 trials PROVEN) */
/* net-core FUN_0101e660 @ 0x101e660  (parity 300 trials PROVEN) */

extern int FUN_0101f8d8(void);
extern void FUN_0100d584(int, void*);
__attribute__((naked)) void FUN_0101e660(void)
{
    __asm__ volatile(
        "ldr r3, =0x21000eac\n"
        "push {r0,r1,r2,r4,r5,r6,r7,lr}\n"
        "ldrb r4, [r3,#0x12]\n"
        "mov r6, r0\n"
        "ldrb r5, [r3,#0x13]\n"
        "ldrh r7, [r3,#0x14]\n"
        "cbnz r4, 1f\n"
        "bl FUN_0101f8d8\n"
        "mov r4, r0\n"
        "1:\n"
        "cbnz r5, 4f\n"
        "bl FUN_0101f8d8\n"
        "mov r5, r0\n"
        "cbnz r4, 2f\n"
        "3:\n"
        "movs r0, #9\n"
        "add sp, #0xc\n"
        "pop {r4,r5,r6,r7,pc}\n"
        "2:\n"
        "cmp r0, #0\n"
        "beq 3b\n"
        "5:\n"
        "mov r0, r6\n"
        "add r1, sp, #4\n"
        "strb.w r4, [sp,#4]\n"
        "strb.w r5, [sp,#5]\n"
        "strh.w r7, [sp,#6]\n"
        "bl FUN_0100d584\n"
        "movs r0, #0\n"
        "b 100f\n"
        "4:\n"
        "cmp r4, #0\n"
        "bne 5b\n"
        "b 3b\n"
        "100:\n"
        "add sp, #0xc\n"
        "pop {r4,r5,r6,r7,pc}\n"
    );
}




