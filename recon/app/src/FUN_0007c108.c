/* Reconstructed FUN_0007c108 @ 0x7c108  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
extern int FUN_000559fc(void);
int FUN_0007c108(void)
{
    int iVar1 = FUN_000167a8();
    if (*(volatile char*)(iVar1 + 0x1058) == 2) {
        iVar1 = FUN_000559fc();
        if (iVar1 != 0) {
            return iVar1;
        }
        iVar1 = FUN_000167a8();
        *(volatile char*)(iVar1 + 0x1058) = 3;
    }
    return 0;
}

