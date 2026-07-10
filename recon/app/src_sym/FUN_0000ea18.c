/* Reconstructed FUN_0000ea18 @ 0xea18  (parity: 300/300 trials, PROVEN) */

void FUN_0000ea18(int param_1, int param_2, unsigned int *param_3)
{
    int iVar2 = 0;
    int iVar4 = 0;
    int iVar3 = 0;
    char *pcVar1 = (char*)(param_1 - 1);
    *param_3 = 1;
    while (1) {
        pcVar1 = pcVar1 + 1;
        iVar3 = iVar4 + 1;
        iVar2 = iVar2 + 1;
        char c = *(volatile char*)pcVar1;
        if (c != 0) {
            *(volatile unsigned int*)(param_2 + iVar4*4) = iVar2;
            iVar4 = iVar3;
            if (iVar3 > 2) break;
        }
        if (iVar2 == 3) {
            param_3[1] = iVar4;
            return;
        }
    }
    param_3[1] = iVar3;
}

