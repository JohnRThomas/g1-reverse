/* Reconstructed FUN_0007db50 @ 0x7db50  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007dac0(void);
extern int FUN_000167a8(void);
extern int FUN_0000e1a4(int param_1, int param_2, int param_3, int param_4, int param_5);

void FUN_0007db50(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;
    int iVar3;

    uVar1 = FUN_0007dac0();
    if (uVar1 < 7) {
        iVar2 = FUN_000167a8();
        iVar3 = FUN_0000e1a4(param_1, param_2, 1000, 0, param_4);
        iVar2 = uVar1 * 0xc + iVar2;
        *(int *)(iVar2 + 0x1136) = *(int *)(iVar2 + 0x1136) + iVar3;
        iVar2 = FUN_000167a8();
        *(int *)(iVar2 + 0x10d2) = *(int *)(iVar2 + 0x10d2) + iVar3;
    }
}

