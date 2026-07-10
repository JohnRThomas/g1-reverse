/* Reconstructed FUN_0008199a @ 0x8199a  (parity: 300/300 trials, PROVEN) */

extern int FUN_00057394(void);
extern int FUN_000573f4(int a, int b, int c);
extern short *FUN_0005f5d0(int a, int b);
extern void FUN_00081962(int a, int b, int c, int d, int e);

unsigned int FUN_0008199a(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;
    short *puVar3;

    uVar1 = FUN_00057394();
    *(char *)(param_1 + 0xb8) = (char)uVar1;
    iVar2 = FUN_000573f4(0x14, uVar1, 10);
    if (iVar2 == 0) {
        uVar1 = 0xfffffff4;
    } else {
        puVar3 = FUN_0005f5d0(iVar2 + 0xc, 10);
        *puVar3 = *(short *)(param_1 + 0xb6);
        puVar3[1] = *(short *)(param_1 + 0x14);
        puVar3[2] = *(short *)(param_1 + 0x16);
        puVar3[3] = *(short *)(param_1 + 0x18);
        puVar3[4] = (short)*(int *)(param_1 + 0x1c);
        FUN_00081962(param_1, iVar2, 0x140000, 0, param_4);
        uVar1 = 0;
    }
    return uVar1;
}

