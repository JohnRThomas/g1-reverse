/* Reconstructed FUN_00033cdc @ 0x33cdc  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00033cdc(void)
{
    unsigned int uVar1 = 0;
    unsigned int base = 0x20007dacUL /* device_info_t+0x13B0  (message/display region) */;
    while (1) {
        if (*(volatile unsigned char*)(base + 0x10) == 0) {
            return uVar1 & 0xff;
        }
        uVar1 = uVar1 + 1;
        base = base + 0x1b4;
        if (uVar1 == 10) {
            break;
        }
    }
    return 10;
}

