/* Reconstructed read_usr_settting_from_flash @ 0x23400  (parity: 300/300 trials, PROVEN) */
extern void memset_bytes(void *a0, unsigned int a1, unsigned int a2);
extern int flash_settings_read(unsigned int a0, void *a1, unsigned int a2);
extern void DEBUG_PRINT(unsigned int a0, unsigned int a1);
extern void debug_print(void);

unsigned int read_usr_settting_from_flash(unsigned char *param_1)
{
    unsigned char buf[32];
    int iVar1;
    unsigned int uVar2;
    memset_bytes(buf, 0, 0x20);
    iVar1 = flash_settings_read(0x134000UL, buf, 0x20UL);
    if (iVar1 == 0) {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0)
                DEBUG_PRINT(0x9e60cUL, 0x9e72aUL);
            else
                debug_print();
        }
        param_1[0x15] = buf[0x15];
        *(unsigned short*)(param_1 + 0x16) = *(unsigned short*)(buf + 0x16);
        uVar2 = 0;
    } else {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0)
                DEBUG_PRINT(0x9e708UL, 0x9e72aUL);
            else
                debug_print();
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

