/* Reconstructed FUN_00063778 @ 0x63778  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_0007e2ec(unsigned int, unsigned int);
extern void FUN_00063654(unsigned int, unsigned int, unsigned int,
                         unsigned int, unsigned int, unsigned int,
                         unsigned int);

void FUN_00063778(int param_1, unsigned int param_2, unsigned int param_3,
                  unsigned int param_4, unsigned int param_5,
                  unsigned int param_6)
{
    if (param_1 != 1) {
        FUN_0007e2fa(0x99cbdUL, 0xf66a6UL, 0xf6659UL, 0x18dUL, param_1, param_2, param_3, param_4);
        FUN_0007e2ec(0xf6659UL, 0x18dUL);
    }
    FUN_00063654((unsigned int)param_1, param_5, param_3, param_4,
                 param_5, param_6, 0);
}
