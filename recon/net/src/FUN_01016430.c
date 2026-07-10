/* net-core FUN_01016430 @ 0x1016430  (parity 300 trials PROVEN) */

extern void FUN_01008d00(void);
extern void FUN_0100a5b4(void);
extern void FUN_010202fc(void);
extern void FUN_010204f4(void);
extern void FUN_01020764(void);
extern void FUN_01021108(void);
extern void FUN_010212ec(void);

__attribute__((naked)) void FUN_01016430(void)
{
    __asm__ volatile(
        "push {r3, r4, r5, r6, r7, lr}\n"
        "ldr r4, =0x21000f90\n"
        "mov r5, r0\n"
        "ldr r2, =0x0103c24c\n"
        "mov r6, r1\n"
        "ldrb.w r3, [r4, #0x7a]\n"
        "ldrb r7, [r2, r3]\n"
        "mov r0, r7\n"
        "bl FUN_010204f4\n"
        "ldrb.w r3, [r4, #0x98]\n"
        "strb.w r7, [r4, #0x8f]\n"
        "add r4, r3\n"
        "ldrb.w r4, [r4, #0xbd]\n"
        "subs r3, r4, #1\n"
        "cmp r3, #7\n"
        "bhi 6f\n"
        "tbb [pc, r3]\n"
        "1:\n"
        ".byte (2f-1b)/2\n"
        ".byte (5f-1b)/2\n"
        ".byte (6f-1b)/2\n"
        ".byte (2f-1b)/2\n"
        ".byte (6f-1b)/2\n"
        ".byte (6f-1b)/2\n"
        ".byte (6f-1b)/2\n"
        ".byte (2f-1b)/2\n"
        ".align 1\n"
        "2:\n"
        "bl FUN_0100a5b4\n"
        "cmp r0, #0x40\n"
        "it hs\n"
        "movhs r0, #0x40\n"
        "uxtb r0, r0\n"
        "3:\n"
        "mov r1, r4\n"
        "bl FUN_010202fc\n"
        "mov r0, r6\n"
        "bl FUN_01020764\n"
        "mov r1, r4\n"
        "movs r0, #1\n"
        "cbz r5, 4f\n"
        "bl FUN_010212ec\n"
        "subs r0, #0\n"
        "it ne\n"
        "movne r0, #1\n"
        "pop {r3, r4, r5, r6, r7, pc}\n"
        "4:\n"
        "bl FUN_01021108\n"
        "movs r0, #1\n"
        "pop {r3, r4, r5, r6, r7, pc}\n"
        "5:\n"
        "movs r0, #0xd\n"
        "b 3b\n"
        "6:\n"
        "movw r1, #0x90f\n"
        "movs r0, #0x32\n"
        "bl FUN_01008d00\n"
    );
}

