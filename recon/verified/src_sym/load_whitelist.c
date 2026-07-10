/* Reconstructed load_whitelist @ 0x34b34  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern unsigned int flash_settings_read(unsigned int, void*, int);
extern void memcpy(unsigned int, void*, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int load_whitelist(void)
{
    unsigned int uVar1;
    unsigned int uVar2, uVar3;
    unsigned char buf[0x15e2];

    memset_bytes(buf, 0, 0x15e2);
    uVar1 = flash_settings_read(0x131000, buf, 0x15e2);
    if (uVar1 == 0) {
        uVar1 = (unsigned int)buf[1];
        if (uVar1 < 0x65) {
            memcpy(0x2001a22cUL, buf, 0x15e2);
            return 0;
        }
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ != 0) {
            uVar3 = 0x36;
            uVar2 = 0xa842e;
            debug_print(uVar2, 0xa8aa8, uVar3, uVar1);
            return 0xffffffff;
        }
        uVar3 = 0x36;
        uVar2 = 0xa842e;
    } else {
        if (*(volatile unsigned int*)0x20007554UL != 0) {
            uVar3 = 0x30;
            uVar2 = 0xa8400;
            debug_print(uVar2, 0xa8aa8, uVar3, uVar1);
            return 0xffffffff;
        }
        uVar3 = 0x30;
        uVar2 = 0xa8400;
    }
    DEBUG_PRINT(uVar2, 0xa8aa8, uVar3, uVar1);
    return 0xffffffff;
}

