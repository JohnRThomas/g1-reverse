/* Reconstructed FUN_000836f8 @ 0x836f8  (parity: 300/300 trials, PROVEN) */

extern unsigned char *FUN_0005f518(unsigned int a, unsigned int b);

void FUN_000836f8(unsigned int param_1, unsigned int param_2)
{
    unsigned char *puVar1 = FUN_0005f518(param_1, 2);
    puVar1[0] = (unsigned char)param_2;
    puVar1[1] = (unsigned char)(param_2 >> 8);
}

