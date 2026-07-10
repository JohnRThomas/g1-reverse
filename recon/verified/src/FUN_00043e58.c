/* Reconstructed FUN_00043e58 @ 0x43e58  (parity: 300/300 trials, PROVEN) */

int FUN_00043e58(unsigned int param_1, unsigned int param_2)
{
    int iVar1 = 0;
    int iVar2 = 0;
    unsigned int uVar3;
    int count = *(volatile int*)0x8ac28UL;
    while (iVar2 < count) {
        uVar3 = *(volatile unsigned short*)(0x9890cUL + iVar2 * 4);
        iVar2 = iVar2 + 1;
        if (uVar3 == param_1) {
            iVar1 = iVar1 + 1;
        }
        if (uVar3 == param_2) {
            iVar1 = iVar1 + 1;
        }
    }
    if (iVar1 > 1) {
        iVar1 = 2;
    }
    return iVar1;
}

