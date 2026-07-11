/* Reconstructed FUN_0005f200 @ 0x5f200  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007e2ec(unsigned int a, unsigned int b);
extern void FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00086502(int);

void FUN_0005f200(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        unsigned long long r;
        FUN_0007e2fa(0x00099cbdUL, 0x000f5402UL, 0x000f539aUL, 0x1c7);
        uVar1 = 0x1c7;
        r = FUN_0007e2ec(0x000f539aUL, uVar1);
        param_1 = (int)r; param_2 = (int)(r >> 32);
    }
    if (param_2 == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f45beUL, 0x000f539aUL, 0x1c8);
        uVar1 = 0x1c8;
        {
          unsigned long long r = FUN_0007e2ec(0x000f539aUL, uVar1);
          param_1 = (int)r; param_2 = (int)(r >> 32);
        }
    }
    FUN_00086502(param_1);
}
