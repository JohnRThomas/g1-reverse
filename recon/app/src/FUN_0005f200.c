/* Reconstructed FUN_0005f200 @ 0x5f200  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(unsigned int a, unsigned int b);
extern void FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_00086502(void);

void FUN_0005f200(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f5402UL, 0x000f539aUL, 0x1c7, param_4);
        uVar1 = 0x1c7;
    } else {
        if (param_2 != 0) {
            FUN_00086502();
            return;
        }
        FUN_0007e2fa(0x00099cbdUL, 0x000f45beUL, 0x000f539aUL, 0x1c8, param_4);
        uVar1 = 0x1c8;
    }
    FUN_0007e2ec(0x000f539aUL, uVar1);
}

