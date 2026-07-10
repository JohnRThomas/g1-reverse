/* Reconstructed FUN_0008509e @ 0x8509e  (parity: 300/300 trials, PROVEN) */

extern int FUN_00064c5c(int);
extern int FUN_0006466c(int,int,int,int);
extern void FUN_00064b1c(int);
int FUN_0008509e(int param_1,int param_2,int param_3)
{
    int uVar1 = FUN_00064c5c(param_3);
    int iVar2 = FUN_0006466c(param_1,param_2,uVar1,0);
    if (iVar2 == 0) {
        FUN_00064b1c(uVar1);
        uVar1 = 0;
    }
    return uVar1;
}

