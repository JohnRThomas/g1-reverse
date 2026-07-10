/* Reconstructed FUN_00024f08 @ 0x24f08  (parity: 300/300 trials, PROVEN) */

extern int FUN_000256dc(unsigned int, int, int, int, unsigned int);

int FUN_00024f08(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = FUN_000256dc(*(volatile unsigned int*)0x20007a44UL /* device_info.gap_1030+24 */, 0, param_1, 4, param_4);
    if (*(volatile char*)(param_1+2) == 0) {
        if (iVar2 != 0) return -1;
        iVar2 = FUN_000256dc(*(volatile unsigned int*)0x20007a44UL /* device_info.gap_1030+24 */, 4, param_1 + 4, 4, param_4);
    }
    if (iVar2 != 0) iVar2 = 1;
    return -iVar2;
}

