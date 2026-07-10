#include "g1_net_symbols.h"
/* net-core FUN_01017018 @ 0x1017018  (parity 300 trials PROVEN) */

extern int FUN_0101f8d8(void);
extern unsigned int FUN_010202a8(void);
extern unsigned int FUN_0101b15c(void*, unsigned int, unsigned short, void*);

__attribute__((naked)) unsigned int FUN_01017018(void *param_1, unsigned char *param_2, unsigned int param_3, void *param_4)
{
    __asm__ volatile(
        "push {r3, r4, r5, lr}\n"
        "mov r5, r0\n"
        "mov r4, r1\n"
        "bl FUN_0101f8d8\n"
        "lsls r2, r0, #0x1d\n"
        "bmi 1f\n"
        "ldrb r3, [r4, #2]\n"
        "and r3, r3, #0xe0\n"
        "cmp r3, #0x40\n"
        "beq 2f\n"
        "1:\n"
        "bl FUN_0101f8d8\n"
        "lsls r3, r0, #0x1e\n"
        "bmi 3f\n"
        "ldrb r3, [r4, #2]\n"
        "and r3, r3, #0xe0\n"
        "cmp r3, #0x20\n"
        "beq 2f\n"
        "3:\n"
        "ldrb r3, [r4]\n"
        "and r3, r3, #0x3f\n"
        "cmp r3, #0x24\n"
        "bls 4f\n"
        "2:\n"
        "movs r0, #0\n"
        "pop {r3, r4, r5, pc}\n"
        "4:\n"
        "bl FUN_010202a8\n"
        "ldrsb.w r3, [r4]\n"
        "ldrb r1, [r4, #2]\n"
        "cmp r3, #0\n"
        "ldrb r2, [r4, #1]\n"
        "and r3, r1, #0x1f\n"
        "ite ge\n"
        "movge.w ip, #0x1e\n"
        "movlt.w ip, #0x12c\n"
        "orr.w r3, r2, r3, lsl #8\n"
        "mul r3, ip, r3\n"
        "subs r2, r3, r0\n"
        "cmp.w r2, #0x10e\n"
        "blo 2b\n"
        "cmp r0, r3\n"
        "bhi 2b\n"
        "ldr r3, =0x21000f90\n"
        "mov r0, r5\n"
        "ldrh r2, [r4]\n"
        "strb.w r1, [r3, #0xbc]\n"
        "strh.w r2, [r3, #0xba]\n"
        "pop.w {r3, r4, r5, lr}\n"
        "b.w FUN_0101b15c\n"
    );
}

