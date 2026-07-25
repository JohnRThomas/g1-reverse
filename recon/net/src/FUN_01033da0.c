/* net-core FUN_01033da0 @ 0x1033da0  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* Undo of FUN_01033d54 @ 0x01033da0 (Ghidra-gap leaf, extent 0x32). */
void FUN_01033da0(void)
{
    unsigned int chD = *(volatile unsigned char *)0x21006460u;
    unsigned int chE = *(volatile unsigned char *)0x2100645fu;

    *(volatile unsigned int *)(0x4100f000u + 0x508u) = (1u << chD) | (1u << chE);
    *(volatile unsigned int *)(0x41008000u + 0x184u) = 0u;
    *(volatile unsigned int *)(0x41019000u + 0x1c0u) = 0u;
    *(volatile unsigned int *)(0x41019000u + 0x90u) = 0u;
    *(volatile unsigned int *)(0x41008000u + 0x90u) = 0u;
}
