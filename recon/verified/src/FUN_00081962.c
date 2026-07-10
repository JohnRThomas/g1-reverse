/* Reconstructed FUN_00081962 @ 0x81962  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00081820(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);
extern void FUN_0005f24c(unsigned int a);
extern void FUN_0007350c(unsigned int *a, unsigned int b, unsigned int c, unsigned int d);

void FUN_00081962(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned long long uVar1;
    uVar1 = FUN_00081820(*param_1, 5, param_2, 0, 0, param_2, param_3);
    if ((int)uVar1 != 0) {
        FUN_0005f24c(param_2);
        return;
    }
    FUN_0007350c(param_1 + 0x30, (unsigned int)(uVar1 >> 32), param_3, param_4);
}

