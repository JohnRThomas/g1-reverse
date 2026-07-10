/* Reconstructed FUN_00080f56 @ 0x80f56  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00053cd4(int a, int b);
extern short *FUN_0005f5d0(int a, int b);
extern void FUN_000543d8(int a, int b);
extern void FUN_000534a8(void);

void FUN_00080f56(short param_1, unsigned char param_2, int param_3, int param_4)
{
    unsigned long long uVar3 = FUN_00053cd4(0x2021, 3);
    int iVar1 = (int)uVar3;
    if (iVar1 == 0) {
        FUN_000534a8();
        return;
    }
    short *puVar2 = FUN_0005f5d0(iVar1 + 0xc, 3);
    *(volatile short *)puVar2 = param_1;
    *(volatile unsigned char *)((char *)puVar2 + 2) = param_2;
    FUN_000543d8(0x2021, iVar1);
}

