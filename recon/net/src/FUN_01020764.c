/* net-core FUN_01020764 @ 0x1020764  (parity 300 trials PROVEN) */
extern void FUN_01008d00(int a, int b, ...);
extern int FUN_01023ac4(void);

void FUN_01020764(unsigned int param_1, unsigned int param_2, unsigned int param_3,
                   unsigned int param_4)
{
    unsigned int iVar2 = 0x41008000;
    unsigned int iVar3 = 0x210015f0;
    unsigned char bVar1 = *(volatile unsigned char *)(iVar3 + 0x35);
    unsigned int uVar4 = (unsigned int)bVar1;

    *(volatile unsigned int *)(iVar2 + 0x504) = param_1;
    *(volatile unsigned int *)(iVar3 + 0x30) = param_1;
    *(volatile unsigned char *)(iVar3 + 0x35) = (unsigned char)(bVar1 | 1);

    if ((int)(uVar4 << 0x1e) < 0) {
        *(volatile unsigned int *)(iVar2 + 0x200) =
            *(volatile unsigned int *)(iVar2 + 0x200) | 1;
        if ((*(volatile unsigned int *)(iVar2 + 0x550) & 0xf6) == 2) {
            FUN_01008d00(0x3e, 0x5a7, uVar4, 2, param_4);
        }
    }
    if ((int)(uVar4 << 0x1d) < 0) {
        *(volatile unsigned int *)(iVar2 + 0x88) = 0x80000008;
        int r = FUN_01023ac4();
        if (r != 0) {
            FUN_01008d00(0x3e, 0x5af);
        }
    }
}


