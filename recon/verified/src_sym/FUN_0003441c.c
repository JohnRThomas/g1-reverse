/* Reconstructed FUN_0003441c @ 0x3441c  (parity: 300/300 trials, PROVEN) */

void FUN_0003441c(void)
{
    unsigned int idx = *(volatile unsigned char*)0x2001a22aUL;
    unsigned int base = idx * 0x1b4 + 0x20007dacUL /* device_info_t+0x13B0  (message/display region) */;
    int iVar1 = *(volatile int*)(base + 4);
    if (iVar1 != 0) {
        *(volatile int*)(base + 4) = iVar1 - 10;
    }
}

