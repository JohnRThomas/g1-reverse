/* Reconstructed FUN_00018334 @ 0x18334  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007ddbe(void *dst, unsigned int n, unsigned int fmt, ...);
extern void FUN_00086fee(void *dst, unsigned int src);

void FUN_00018334(unsigned char *param_1, void *param_2)
{
    unsigned int uVar1;
    unsigned char auStack_1c[12];
    switch (param_1[0]) {
    case 0: uVar1 = 0x0009a1c8u; break;
    case 1: uVar1 = 0x0009a1cfu; break;
    case 2: uVar1 = 0x0009a1d6u; break;
    case 3: uVar1 = 0x0009a1e0u; break;
    default:
        FUN_0007ddbe(auStack_1c, 10, 0x000f5071u);
        goto LAB;
    }
    FUN_00086fee(auStack_1c, uVar1);
LAB:
    FUN_0007ddbe(param_2, 0x1e, 0x0009a1eau,
        param_1[6], param_1[5], param_1[4], param_1[3],
        param_1[2], param_1[1], auStack_1c);
}
