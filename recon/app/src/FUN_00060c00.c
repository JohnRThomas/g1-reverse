/* Reconstructed FUN_00060c00 @ 0x60c00  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005010c(int,...);
extern int FUN_00060990(int,...);
extern int FUN_00060a10(int,...);
extern int FUN_00060a5c(int,...);
extern int FUN_00060ab0(int,...);
extern int FUN_00066994(int,...);
extern int FUN_000838d6(int,...);
extern int FUN_000838dc(int,...);
extern int FUN_0008397e(int,...);
extern int FUN_000839a6(int,...);
extern int FUN_00086be4(int,...);

int FUN_00060c00(int param_1)
{
    int iVar1, iVar4;
    unsigned uVar5;

    iVar1 = FUN_000838dc(0);
    if (iVar1 < 0) return iVar1;
    FUN_0005010c(0);
    iVar4 = *(int *)(param_1 + 4);
    *(volatile int *)0x500055b8UL = 0;
    FUN_00066994(0);
    *(volatile int *)0x500055b8UL = 2;
    iVar1 = FUN_00060990(0);
    if (iVar1 < 0) return iVar1;
    iVar1 = FUN_0008397e(0);
    if (iVar1 < 0) return iVar1;

    if (((unsigned)*(unsigned char *)(iVar4 + 0x1d) - 2u) < 2u) uVar5 = 1;
    else if (((unsigned)*(unsigned char *)(iVar4 + 0x1c) - 3u) < 2u) uVar5 = 1;
    else uVar5 = 0;

    iVar1 = FUN_000839a6(0);
    if (iVar1 < 0) { FUN_000838d6(0); return iVar1; }

    if (uVar5 != ((unsigned)(iVar1 << 25) >> 31)) {
        iVar1 = FUN_00060ab0(0);
        if (iVar1 != 0) {
            if (iVar1 >= 0) return iVar1;
            FUN_000838d6(0);
            return iVar1;
        }
        do {
            iVar1 = FUN_000839a6(0);
            if (iVar1 < 0) { FUN_000838d6(0); return iVar1; }
        } while (iVar1 & 1);
    }

    FUN_00060a5c(0);
    iVar1 = FUN_00060a10(0);
    if (iVar1 == 0) {
        iVar1 = FUN_00060ab0(0);
        FUN_00060a5c(0);
        if (iVar1 == 0) {
            iVar4 = *(int *)(param_1 + 4);
            iVar1 = FUN_00086be4(0);
            if (iVar1 == 0) return 0;
            FUN_000838d6(0);
        }
    } else {
        FUN_00060a5c(0);
    }
    return -0x13;
}

