/* Reconstructed FUN_00065418 @ 0x65418  (parity: 300/300 trials, PROVEN) */

extern void FUN_00064ef8(unsigned int a, unsigned int b);

void FUN_00065418(unsigned int param_1)
{
    *(volatile unsigned int*)0x50017508UL = 1u << (param_1 & 0xff);
    FUN_00064ef8(0x20002bbcUL, param_1);
}

