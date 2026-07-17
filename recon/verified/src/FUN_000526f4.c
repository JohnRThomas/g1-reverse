/* Reconstructed FUN_000526f4 @ 0x526f4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072e50(int a, unsigned int b);
extern void FUN_0007e2ec(unsigned int a, unsigned int b);
extern void FUN_0007e2fa(unsigned int a, ...);
extern void FUN_00080b28(void);
extern void FUN_000864e8(int a);

unsigned int FUN_000526f4(int param_1)
{
    if (*(volatile int *)(param_1 + 0x2c) == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f293bUL, 0x000f2901UL, 0x92);
        FUN_0007e2fa(0x000f2963UL);
        FUN_0007e2ec(0x000f2901UL, 0x92);
    }
    FUN_00080b28();
    FUN_00072e50(param_1, 0x00080ab5UL);
    FUN_000864e8(param_1 + 0x10);
    return 0;
}
