/* Reconstructed FUN_0007c754 @ 0x7c754  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007c41c(int);
int FUN_0007c754(int *param_1, int *param_2)
{
    if (param_1 == 0 || param_2 == 0) {
        return 7;
    }
    int iVar4 = 0, iVar5 = 0, iVar3;
    for (iVar3 = *param_1; iVar3 != 0; iVar3 = *(int*)(iVar3 + 0x18)) {
        int iVar1 = FUN_0007c41c(iVar3);
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + iVar1;
    }
    param_2[0] = iVar5;
    param_2[1] = iVar4;
    return 0;
}

