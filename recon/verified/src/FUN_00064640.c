/* Reconstructed FUN_00064640 @ 0x64640  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000ef12(unsigned long);
extern int FUN_00086c04(int a, int b, int c);

int FUN_00064640(int param_1)
{
    int iVar1;
    int iVar2;
    if (param_1 != 0) {
        iVar1 = FUN_0000ef12(param_1);
        iVar2 = ((int(*)(int))(*(volatile unsigned int*)0x20002bacUL))(iVar1 + 1);
        if (iVar2 != 0) {
            FUN_00086c04(iVar2, param_1, iVar1 + 1);
            return iVar2;
        }
    }
    return 0;
}

