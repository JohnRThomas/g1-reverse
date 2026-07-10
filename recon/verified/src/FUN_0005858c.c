/* Reconstructed FUN_0005858c @ 0x5858c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00081aca(int a, int b, int c, int d, int e, int f, int g, int h);
extern void FUN_00081ddc(int a, int b, void *c);

unsigned int FUN_0005858c(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1;
    unsigned int uVar2;
    int local[2];

    if (*(char *)(param_1 + 0xd) == 7) {
        iVar1 = FUN_00081aca(param_1, 4, param_3, 7, param_1, param_2, param_3, param_4);
        if (iVar1 != 0 && (*(volatile int *)(iVar1 + 0x118) << 0x1d) < 0) {
            return *(unsigned int *)(iVar1 - 8);
        }
        uVar2 = 0x1040;
    } else {
        uVar2 = 0x1080;
    }
    FUN_00081ddc(0x88100, uVar2, local);
    return 0;
}

