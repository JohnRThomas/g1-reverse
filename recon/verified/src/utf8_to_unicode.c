/* Reconstructed utf8_to_unicode @ 0x477a0  (parity: 300/300 trials, PROVEN) */

typedef unsigned char byte;
typedef unsigned int uint;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, unsigned int);
extern void FUN_000777f0(unsigned int);
extern void FUN_000778d4(unsigned int);

uint utf8_to_unicode(byte *param_1, int param_2)
{
    uint uVar1, uVar2;
    uVar2 = (uint)*param_1;
    if ((uVar2 & 0xf0) == 0xe0) {
        if (param_2 > 2) {
            uVar1 = (param_1[2] & 0x30) | ((param_1[1] & 3) << 6) | (param_1[2] & 0xf);
            uVar2 = ((param_1[1] >> 2) & 0xf) | ((uVar2 & 0xf) << 4);
            return uVar1 | (uVar2 << 8);
        }
        if (*(volatile int*)0x2000230cUL > 3) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xd7499U, 0xd752aU);
            } else {
                FUN_00019c70(0xd7499U, 0xd752aU);
            }
        }
    } else if ((uVar2 & 0xe0) == 0xc0) {
        if (param_2 > 1) {
            uVar1 = (param_1[1] & 0x3f) | ((uVar2 & 3) << 6);
            uVar2 = (uVar2 >> 2) & 7;
            return uVar1 | (uVar2 << 8);
        }
        FUN_000778d4(0xd74afU);
    } else {
        FUN_000777f0(0xd74bdU);
    }
    return 0;
}

