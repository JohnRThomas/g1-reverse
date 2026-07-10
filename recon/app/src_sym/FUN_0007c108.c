/* Reconstructed FUN_0007c108 @ 0x7c108  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern int FUN_000559fc(void);
int FUN_0007c108(void)
{
    int iVar1 = get_device_info();
    if (*(volatile char*)(iVar1 + 0x1058) == 2) {
        iVar1 = FUN_000559fc();
        if (iVar1 != 0) {
            return iVar1;
        }
        iVar1 = get_device_info();
        *(volatile char*)(iVar1 + 0x1058) = 3;
    }
    return 0;
}

