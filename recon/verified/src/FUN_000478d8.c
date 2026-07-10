/* Reconstructed FUN_000478d8 @ 0x478d8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void*, int, int);
extern unsigned int FUN_0000ef12(unsigned int);
extern unsigned short FUN_00047844(unsigned int, unsigned int, unsigned int, int);

unsigned int FUN_000478d8(unsigned int param_1, unsigned short *param_2)
{
    unsigned int uVar1 = 0x2000f704U;
    unsigned short uVar2;
    unsigned int uVar3;
    FUN_00086c78((void*)uVar1, 0, 0x800);
    uVar3 = FUN_0000ef12(param_1);
    uVar2 = FUN_00047844(param_1, uVar3, uVar1, 0x400);
    *param_2 = uVar2;
    return uVar1;
}

