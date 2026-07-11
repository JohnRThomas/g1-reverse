/* Reconstructed FUN_0004d8f8 @ 0x4d8f8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(int a, int b, int c, int d);
extern void FUN_0007e2ec(int a, int b) __attribute__((noreturn));
extern void FUN_0004d44c(void);

void FUN_0004d8f8(int param_1, unsigned int param_2, unsigned char param_3)
{
    volatile unsigned char index = (unsigned char)(((param_1 - 0x882a0) >> 4) + 1);
    if (param_1 == 0) {
        FUN_0007e2fa(0x99cbd, 0xf0ddf, 0xf0da7, 0xdf);
        FUN_0007e2ec(0xf0da7, 0xdf);
    }
    *(unsigned char *)(*(int *)(param_1 + 4) + 4) = index;
    *(unsigned char *)(*(int *)(param_1 + 4) + 6) = param_3;
    **(unsigned int **)(param_1 + 4) = param_2;
    *(unsigned char *)(*(int *)(param_1 + 4) + 5) = 1;
    FUN_0004d44c();
}
