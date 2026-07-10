/* Reconstructed FUN_0007cfac @ 0x7cfac  (parity: 300/300 trials, PROVEN) */

extern void FUN_0003016c(int a);
extern int FUN_000302f8(unsigned int a, int *b);

int FUN_0007cfac(void)
{
    int iVar1;
    int iVar2 = 100;
    int local_c = 0;
    int bVar3;
    do {
        iVar1 = FUN_000302f8(0x4714, &local_c);
        if (iVar1 != 0) {
            return iVar1;
        }
        if (local_c == 0) break;
        FUN_0003016c(1);
        bVar3 = iVar2 != 0;
        iVar2 = iVar2 - 1;
    } while (bVar3);
    iVar1 = -1;
    if (iVar2 != -1) {
        iVar1 = 0;
    }
    return iVar1;
}

