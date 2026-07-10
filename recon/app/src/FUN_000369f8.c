/* Reconstructed FUN_000369f8 @ 0x369f8  (parity: 300/300 trials, PROVEN) */

void FUN_000369f8(void)
{
    *(volatile unsigned char*)0x2001b811UL = 1;
    unsigned char bVar1 = (unsigned char)(*(volatile unsigned char*)0x2001b810UL + 1);
    if (bVar1 >= 5) {
        bVar1 = 0;
    }
    *(volatile unsigned char*)0x2001b810UL = bVar1;
}

