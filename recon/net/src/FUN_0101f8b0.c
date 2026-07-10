/* net-core FUN_0101f8b0 @ 0x101f8b0  (parity 300 trials PROVEN) */

#define DAT_0101f8c8 ((unsigned int)0x21000020)

void FUN_0101f8b0(unsigned int param_1)
{
    unsigned int idx = param_1 >> 3;
    unsigned char mask = (unsigned char)(1 << (param_1 & 7));
    *(volatile unsigned char *)(DAT_0101f8c8 + idx) = *(volatile unsigned char *)(DAT_0101f8c8 + idx) & ~mask;
    return;
}

