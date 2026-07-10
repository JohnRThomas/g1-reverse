/* Reconstructed FUN_000579d0 @ 0x579d0  (parity: 300/300 trials, PROVEN) */

extern void FUN_000864e8(int);
extern void FUN_00086502(int,int);
extern void FUN_00086c78(int,int,int);
void FUN_000579d0(void)
{
    FUN_000864e8(0x20003a44);
    int uVar1 = 0x20003a44;
    int iVar3 = 0;
    int iVar2 = 0x2000ad34;
    do {
        FUN_00086c78(iVar2, 0, 0x10);
        iVar3 = iVar3 + 1;
        FUN_00086502(uVar1, iVar2);
        iVar2 = iVar2 + 0x10;
    } while (iVar3 != 10);
}

