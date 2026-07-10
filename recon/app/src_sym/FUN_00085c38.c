/* Reconstructed FUN_00085c38 @ 0x85c38  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00085c12(int iVar2);
extern void FUN_00085c26(int *param_1, int param_2);

int FUN_00085c38(int *param_1)
{
    int *puVar1;
    int iVar2;
    int *puVar3;
    unsigned long long uVar5;
    int *puVar4;

    iVar2 = param_1[5];
    uVar5 = FUN_00085c12(iVar2);
    if ((int)uVar5 != 0) {
        if (*(unsigned int *)(iVar2 + 4) < *(unsigned int *)(iVar2 + 8)) {
            *(unsigned char *)((int)param_1 + 0x11) = 0;
            *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1;
            puVar1 = (int *)((((int *)param_1[5])[1] + -1) * 0x18 + *(int *)param_1[5]);
            puVar3 = param_1;
            do {
                puVar4 = puVar3 + 1;
                *puVar1 = *puVar3;
                puVar1 = puVar1 + 1;
                puVar3 = puVar4;
            } while (puVar4 != param_1 + 6);
            param_1[2] = (int)(uVar5 >> 0x20);
            return (int)uVar5;
        }
        FUN_00085c26(param_1, 1);
    }
    return 0;
}

