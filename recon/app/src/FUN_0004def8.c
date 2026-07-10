/* Reconstructed FUN_0004def8 @ 0x4def8  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007ef1c(unsigned int, void*, unsigned int, unsigned int, unsigned int);
extern void FUN_0004dfb8(unsigned int);
extern void FUN_0007eece(unsigned int);

void FUN_0004def8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2;
    unsigned int uStack_c = param_2;
    unsigned int uStack_8 = param_3;
    iVar2 = FUN_0007ef1c(0x87bc0U, (char*)&uStack_c + 3, param_3, param_4, param_1);
    if (iVar2 == 0 && *((unsigned char*)&uStack_c + 3) == 1) {
        FUN_0004dfb8(0x87bc0U);
    }
    unsigned int uVar1 = 0x8ad08U;
    *(volatile unsigned char*)0x2001d44eUL = 1;
    FUN_0007eece(uVar1);
    return;
}

