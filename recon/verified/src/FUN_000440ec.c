/* Reconstructed FUN_000440ec @ 0x440ec  (parity: 300/300 trials, PROVEN) */
extern int FUN_000167a8(int,...);
extern int FUN_000431a8(int,...);
extern int FUN_000432d0(int,...);
extern int FUN_000432ec(int,...);
extern int FUN_00043e90(int,...);
extern int FUN_000471cc(int,...);
extern int FUN_000473c8(int,...);
extern int FUN_0007d446(int,...);
extern int FUN_0007d5f2(int,...);

void FUN_000440ec(int param_1, int param_2, int param_3, int param_4, int param_5,
                  int param_6, int param_7, int param_8, int param_9)
{
    int iVar3, iVar4;
    volatile int sink;

    iVar3 = FUN_0007d446(0);
    if (iVar3 < 0x21) {
        iVar3 = FUN_000431a8(0);
        if ((iVar3 << 0x1e) < 0) FUN_000471cc(0);
        FUN_000432ec(0);
        FUN_00043e90(0);
        FUN_000432d0(0);
        iVar3 = 0;
        do {
            iVar4 = FUN_000167a8(0);
            sink = *(volatile int *)(iVar4 + 0xeb4);
            iVar4 = FUN_000167a8(0);
            sink = *(volatile int *)(iVar4 + 0xeb8);
            iVar3 = iVar3 + 1;
            FUN_000473c8(0);
        } while (iVar3 != 9);
        FUN_0007d5f2(0);
        iVar3 = FUN_000431a8(0);
        if ((iVar3 << 0x1e) < 0) { FUN_000471cc(0); return; }
    } else {
        iVar3 = FUN_0007d446(0);
        if (0x20 < iVar3) {
            FUN_0007d5f2(0);
            iVar3 = FUN_000431a8(0);
            if ((iVar3 << 0x1e) < 0) FUN_000471cc(0);
            FUN_000432ec(0);
            FUN_00043e90(0);
            FUN_000432d0(0);
            iVar3 = 0;
            do {
                iVar4 = FUN_000167a8(0);
                sink = *(volatile int *)(iVar4 + 0xeb4);
                iVar4 = FUN_000167a8(0);
                sink = *(volatile int *)(iVar4 + 0xeb8);
                iVar3 = iVar3 + 1;
                FUN_000473c8(0);
            } while (iVar3 != 9);
            iVar3 = FUN_000431a8(0);
            if ((iVar3 << 0x1e) < 0) { FUN_000471cc(0); return; }
        }
    }
    (void)sink;
}

