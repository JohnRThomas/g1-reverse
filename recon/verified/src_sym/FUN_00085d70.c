/* Reconstructed FUN_00085d70 @ 0x85d70  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00085d5c(int a);

void FUN_00085d70(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = FUN_00085d5c(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}

