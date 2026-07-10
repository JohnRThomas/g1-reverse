/* Reconstructed FUN_000681cc @ 0x681cc  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,int,int,int);
typedef void (*fn2_t)(int,int);
void FUN_000681cc(int param_1)
{
    int iVar1;
    if ((param_1 != 0) && ((iVar1 = *(volatile int*)(param_1 + 4)) != 0)) {
        fn2_t f = *(volatile fn2_t*)(iVar1 + 0xc);
        if (f != 0) {
            f(iVar1, param_1);
            return;
        }
        return;
    }
    FUN_0007e2fa(0x000f7ad6, 0x00099cbd, 0x000f7a9f, 0x51);
    FUN_0007e2ec(0x000f7a9f, 0x51);
}

