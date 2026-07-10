#include "g1_net_symbols.h"
/* net-core FUN_010312d0 @ 0x10312d0  (parity 300 trials PROVEN) */
/* net-core FUN_010312d0 @ 0x10312d0  (parity 300 trials PROVEN) */

__attribute__((naked)) void FUN_010312d0(void)
{
    __asm__ volatile(
        "cbz r1, Lb130a\n"
        "movs r3,#1\n"
        "ldr r2,=0x2100496c\n"
        "lsls r3,r0\n"
        "Lb12d8:\n"
        "ldaex ip,[r2]\n"
        "orr.w ip, ip, r3\n"
        "stlex r1,ip,[r2]\n"
        "cmp r1,#0\n"
        "bne Lb12d8\n"
        "mov.w r3,#0x10000\n"
        "ldr r2,=0x41016000\n"
        "lsls r3,r0\n"
        "str.w r3,[r2,#0x304]\n"
        "ldr r3,=0x21004964\n"
        "lda r3,[r3]\n"
        "lsrs r3,r0\n"
        "lsls r3,r3,#0x1f\n"
        "ittt mi\n"
        "movmi.w r2,#0x400000\n"
        "ldrmi r3,=0xe000e100\n"
        "strmi.w r2,[r3,#0x100]\n"
        "Lb130a:\n"
        "bx lr\n"
    );
}


