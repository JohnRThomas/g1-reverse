/* Reconstructed load_whitelist @ 0x34b34  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void*, int, int);
extern unsigned int FUN_000225b4(unsigned int, void*, int);
extern void FUN_00086c04(unsigned int, void*, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int load_whitelist(void)
{
    unsigned int uVar1;
    unsigned int uVar2, uVar3;
    unsigned char buf[0x15e2];

    FUN_00086c78(buf, 0, 0x15e2);
    uVar1 = FUN_000225b4(0x131000, buf, 0x15e2);
    if (uVar1 == 0) {
        uVar1 = (unsigned int)buf[1];
        if (uVar1 < 0x65) {
            FUN_00086c04(0x2001a22cUL, buf, 0x15e2);
            return 0;
        }
        if (*(volatile unsigned int*)0x20007554UL != 0) {
            uVar3 = 0x36;
            uVar2 = 0xa842e;
            FUN_00019c70(uVar2, 0xa8aa8, uVar3, uVar1);
            return 0xffffffff;
        }
        uVar3 = 0x36;
        uVar2 = 0xa842e;
    } else {
        if (*(volatile unsigned int*)0x20007554UL != 0) {
            uVar3 = 0x30;
            uVar2 = 0xa8400;
            FUN_00019c70(uVar2, 0xa8aa8, uVar3, uVar1);
            return 0xffffffff;
        }
        uVar3 = 0x30;
        uVar2 = 0xa8400;
    }
    DEBUG_PRINT(uVar2, 0xa8aa8, uVar3, uVar1);
    return 0xffffffff;
}

