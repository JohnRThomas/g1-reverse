/* Reconstructed FUN_00072e50 @ 0x72e50  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(unsigned int a, unsigned int b);
extern void FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00086c78(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_00072e50(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f82e0UL, 0x000f820fUL, 0x89);
        uVar1 = 0x89;
    } else {
        if (param_2 != 0) {
            FUN_00086c78(param_1, 0, 0x10, param_4, param_4);
            *(volatile int *)(param_1 + 4) = param_2;
            return;
        }
        FUN_0007e2fa(0x00099cbdUL, 0x000f8230UL, 0x000f820fUL, 0x8a);
        uVar1 = 0x8a;
    }
    FUN_0007e2ec(0x000f820fUL, uVar1);
}
