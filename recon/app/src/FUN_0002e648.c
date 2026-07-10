/* Reconstructed FUN_0002e648 @ 0x2e648  (parity: 300/300 trials, PROVEN) */

extern int FUN_0002e594(int, void*, unsigned int, unsigned char, unsigned int);

int FUN_0002e648(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int uStack_c;
    unsigned int uStack_8;
    unsigned char g = *(volatile unsigned char*)0x20018da1UL;
    if (g == 0) {
        iVar1 = -1;
    } else {
        uStack_c = param_2;
        uStack_8 = param_3;
        iVar1 = FUN_0002e594(0, (char*)&uStack_c + 2, param_3, g, param_1);
        if (iVar1 != 0) {
            iVar1 = -1;
        } else {
            unsigned short v = *(unsigned short*)((char*)&uStack_c + 2);
            iVar1 = (v & 0xfff) << (v >> 12);
        }
    }
    return iVar1;
}

