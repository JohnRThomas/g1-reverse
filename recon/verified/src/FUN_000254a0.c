/* Reconstructed FUN_000254a0 @ 0x254a0  (parity: 300/300 trials, PROVEN) */

extern int FUN_00025474(void);

void FUN_000254a0(int param_1, unsigned char *param_2)
{
    int iVar1 = FUN_00025474();
    *param_2 = (iVar1 != 0);
    volatile unsigned char *flagp = (volatile unsigned char*)0x20018c68UL;
    if (iVar1 != 0) {
        if (*flagp == 0) {
            *flagp = 1;
        }
    } else {
        if (*flagp != 0) {
            *flagp = 0;
            if (*(volatile char*)((char*)param_1+2) == 0) {
                *(volatile unsigned char*)((char*)param_1+5) = 1;
            }
        }
    }
}

