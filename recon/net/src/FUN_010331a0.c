/* net-core FUN_010331a0 @ 0x10331a0  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB retransmission-window release @ 0x010331a0 (Ghidra-gap, extent 0x22). */
extern void FUN_01033ca4(void);
extern void FUN_010218d8(void);
extern void FUN_010218f0(unsigned int);

void FUN_010331a0(void)
{
    volatile unsigned int *reg;
    FUN_01033ca4();
    FUN_010218d8();
    FUN_010218f0(3u);
    reg = *(volatile unsigned int *volatile *)0x21000698u;
    reg[0x200u / 4u] = reg[0x200u / 4u] & ~0x40004u;
}
