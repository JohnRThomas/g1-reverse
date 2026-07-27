/* Reconstructed FUN_00064c5c @ 0x64c5c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00084fd4(unsigned int a);
extern int FUN_00064640(int);
extern void FUN_00064b1c(unsigned int a);

int FUN_00064c5c(unsigned int param_1)
{
    int iVar1, iVar2;
    iVar1 = FUN_00084fd4(*(volatile unsigned int*)0x20002bacUL);
    if (iVar1 != 0) {
        *(volatile int*)(iVar1 + 0xc) = 0x10;
        iVar2 = FUN_00064640(param_1);
        *(volatile int*)(iVar1 + 0x10) = iVar2;
        if (iVar2 != 0) {
            return iVar1;
        }
        FUN_00064b1c(iVar1);
    }
    return 0;
}

