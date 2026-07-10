/* Reconstructed FUN_0007c360 @ 0x7c360  (parity: 300/300 trials, PROVEN) */

extern int FUN_00022bd0(void);
extern int FUN_00022e78(int);
extern int FUN_000230e0(int);
extern int FUN_000167a8(void);
extern void FUN_0007d1b8(int);
int FUN_0007c360(int param_1)
{
    int iVar1 = FUN_00022bd0();
    if (iVar1 == 0 && (iVar1 = FUN_00022e78(param_1)) == 0 &&
        (iVar1 = FUN_000230e0(param_1)) == 0) {
        int r = FUN_000167a8();
        FUN_0007d1b8(*(int*)(r + 0xff0));
    }
    return 0;
}

