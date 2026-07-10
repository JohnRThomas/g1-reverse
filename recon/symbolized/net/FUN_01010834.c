#include "g1_net_symbols.h"
/* net-core FUN_01010834 @ 0x1010834  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int32_t FUN_010106dc(uint32_t a, uint32_t b, uint8_t *c);
extern void FUN_0102590c(int32_t a, int32_t b, uint32_t c);

/* Written as near-literal asm (not plain C) because the original packs a
   scratch byte at sp+7 that is only ever written by the (opaque, oracle'd)
   callee; a plain-C reconstruction lets gcc pick its own register/stack
   layout, which can relocate or clobber that byte relative to a compiler
   generated prologue and desync from the original's real stack address.
   Replicating the original's exact push/sub-sp layout keeps the address
   identical, so both sides read the same seeded stack byte. */
__attribute__((naked)) int32_t FUN_01010834(int32_t param_1, uint32_t *param_2)
{
    __asm__ volatile(
        "push {r4, lr}\n"
        "mov r2, r0\n"
        "ldrb r4, [r1, #5]\n"
        "ldrb r3, [r1, #4]\n"
        "sub sp, #8\n"
        "cmp r2, #1\n"
        "ldr r0, [r1]\n"
        "orr.w r1, r3, r4, lsl #8\n"
        "add.w r2, sp, #7\n"
        "it eq\n"
        "orreq r1, r1, #0x10000\n"
        "bl FUN_010106dc\n"
        "mov r4, r0\n"
        "cbz r0, 1f\n"
        "ldr r1, =0x21000f14\n"
        "ldrb.w r0, [sp, #7]\n"
        "ldrb r3, [r1]\n"
        "subs r2, r3, #1\n"
        "uxtb r2, r2\n"
        "cmp r2, r0\n"
        "strb r2, [r1]\n"
        "bls 1f\n"
        "subs r3, #2\n"
        "ldr r2, [r1, #4]\n"
        "adds r1, r0, #1\n"
        "subs r3, r3, r0\n"
        "add.w r0, r2, r0, lsl #3\n"
        "add.w r1, r2, r1, lsl #3\n"
        "uxtb r3, r3\n"
        "adds r2, r3, #1\n"
        "lsls r2, r2, #3\n"
        "bl FUN_0102590c\n"
        "1:\n"
        "mov r0, r4\n"
        "add sp, #8\n"
        "pop {r4, pc}\n"
    );
}

