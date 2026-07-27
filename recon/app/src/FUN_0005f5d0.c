/* Reconstructed FUN_0005f5d0 @ 0x5f5d0  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00083730(void);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned int a,unsigned int b);

int FUN_0005f5d0(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned short uVar1;
    unsigned int uVar2;
    int iVar3;
    volatile unsigned short *hp = (volatile unsigned short *)((char*)param_1 + 4);
    uVar1 = *hp;
    iVar3 = *(volatile int*)param_1;
    uVar2 = FUN_00083730();
    if (uVar2 < param_2) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f54a8UL, 0x000f543aUL, 0x3e);
        FUN_0007e2ec(0x000f543aUL, 0x3e);
    }
    *hp = uVar1 + (unsigned short)param_2;
    return iVar3 + (unsigned int)uVar1;
}

