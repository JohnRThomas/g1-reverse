/* Reconstructed FUN_00064ca4 @ 0x64ca4  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00084fd4(unsigned int a);

void FUN_00064ca4(void)
{
    unsigned int v = *(volatile unsigned int*)0x20002bacUL;
    unsigned int r = FUN_00084fd4(v);
    if (r != 0) {
        *(volatile unsigned int*)(r + 0xc) = 0x40;
    }
}

