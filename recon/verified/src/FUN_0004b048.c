/* Reconstructed FUN_0004b048 @ 0x4b048  (parity: 300/300 trials, PROVEN) */

void FUN_0004b048(int param_1)
{
    int iVar1;
    int iVar2;
    volatile int *piVar3;

    iVar1 = 0x20002548;
    piVar3 = (volatile int *)(param_1 * 0x28 + 8 + 0x20002548);
    do {
        iVar2 = *piVar3;
        if (iVar2 == 0) {
            return;
        }
    } while (*piVar3 != iVar2);
    *piVar3 = iVar2 - 1;
    if (iVar2 == 1) {
        *(volatile int *)(iVar1 + param_1 * 0x28) = 0;
        *(volatile int *)(iVar1 + param_1 * 0x28 + 4) = 0;
    }
}

