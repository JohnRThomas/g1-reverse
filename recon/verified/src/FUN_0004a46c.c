/* Reconstructed FUN_0004a46c @ 0x4a46c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007d9a4(void);

void FUN_0004a46c(int *param_1, int param_2, int param_3)
{
    volatile int *arr = (volatile int*)0x2000a0a0UL;
    int iVar3;
    if (param_3 == 0) {
        iVar3 = FUN_0007d9a4();
        int iVar4 = arr[param_2];
        if (iVar4 == 0) {
            arr[param_2] = iVar3;
        } else if ((unsigned int)(iVar3 - iVar4) > 999) {
            unsigned int uVar5 = (unsigned int)(iVar3-iVar4)/1000;
            int iv = *param_1;
            arr[param_2] = uVar5*1000 + iVar4;
            *param_1 = iv + uVar5;
        }
    } else {
        int uVar2 = FUN_0007d9a4();
        arr[param_2] = uVar2;
    }
}

