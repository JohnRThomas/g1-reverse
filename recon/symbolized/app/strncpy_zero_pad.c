#include "g1_app_symbols.h"
/* named: strncpy_zero_pad */
/* Reconstructed strncpy_zero_pad @ 0x8705a  (parity: 300/300 trials, PROVEN) */

__attribute__((naked)) void strncpy_zero_pad(char *param_1, int param_2, int param_3)
{
    __asm__ volatile(
        "subs r1, #1\n"
        "mov  r3, r0\n"
        "push {r4, lr}\n"
        "0:\n"
        "cbz  r2, 1f\n"
        "ldrb r4, [r1, #1]!\n"
        "subs r2, #1\n"
        "strb r4, [r3], #1\n"
        "cmp  r4, #0\n"
        "bne  0b\n"
        "1:\n"
        "add  r2, r3\n"
        "movs r1, #0\n"
        "2:\n"
        "cmp  r3, r2\n"
        "bne  3f\n"
        "pop {r4, pc}\n"
        "3:\n"
        "strb r1, [r3], #1\n"
        "b 2b\n"
    );
}

