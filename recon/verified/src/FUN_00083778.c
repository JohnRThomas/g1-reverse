/* Reconstructed FUN_00083778 @ 0x83778  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005f638(void);
void FUN_00083778(int param_1)
{
    int iVar1 = *(volatile int*)(param_1 - 8);
    *(volatile int*)(param_1 - 8) = iVar1 + 1;
    if (iVar1 != 0) {
        *(int*)(param_1 + 0x68) = 0xfffffff0;
        return;
    }
    FUN_0005f638();
}

