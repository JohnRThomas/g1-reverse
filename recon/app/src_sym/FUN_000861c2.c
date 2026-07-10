/* Reconstructed FUN_000861c2 @ 0x861c2  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_000861ae(int a);

void FUN_000861c2(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = FUN_000861ae(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}

