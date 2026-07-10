/* Reconstructed FUN_0007d642 @ 0x7d642  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007d82e(unsigned int, unsigned char*, unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_0007d642(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int stackword = ((param_2 & 0xFFu) << 24) | (param_2 & 0x00FFFFFFu);
    unsigned char *p = ((unsigned char*)&stackword) + 3;
    FUN_0007d82e(param_1, p, 1, param_4, param_1, stackword);
}

