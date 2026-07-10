/* Reconstructed FUN_0007fc04 @ 0x7fc04  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007fb20(unsigned int a, unsigned int b);
extern int FUN_0007f97c(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

int FUN_0007fc04(unsigned int param_1, unsigned int param_2)
{
    int iVar1, iVar2, iVar3;
    iVar1 = FUN_0007fb20(param_1, 2);
    iVar2 = FUN_0007f97c(param_1, 0x46, param_2, 2);
    iVar3 = FUN_0007fb20(param_1, 0);
    return iVar3 + iVar1 + iVar2;
}

