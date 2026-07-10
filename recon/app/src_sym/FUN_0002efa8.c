/* Reconstructed FUN_0002efa8 @ 0x2efa8  (parity: 300/300 trials, PROVEN) */

extern unsigned char *get_device_info(void);

unsigned char FUN_0002efa8(void)
{
    unsigned char *pcVar2 = get_device_info();
    unsigned char uVar1;
    if (*pcVar2 == 1) {
        uVar1 = *(volatile unsigned char*)0x2000302fUL;
    } else {
        uVar1 = 0;
    }
    return uVar1;
}

