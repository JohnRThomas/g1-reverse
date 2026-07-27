/* Reconstructed FUN_00030c90 @ 0x30c90  (parity: 300/300 trials, PROVEN) */

extern int FUN_00030b3c(int *);

void FUN_00030c90(void)
{
    int iVar1 = FUN_00030b3c(0x20002408UL);
    if (iVar1 >= 0) {
        *(volatile unsigned int*)0x20007bccUL /* device_info_t+0x11D0  (device-state region) */ = 1;
    }
}

