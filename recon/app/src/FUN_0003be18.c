/* Reconstructed FUN_0003be18 @ 0x3be18  (parity: 300/300 trials, PROVEN) */
extern int FUN_000167a8(void);
extern void FUN_00043308(void);
extern void FUN_00043324(int a0,int a1);
extern void FUN_0004334c(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7);
extern void FUN_00047260(int a0,int a1,int a2,int a3,int a4,int a5);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);

int FUN_0003be18(unsigned char *param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar5 = *param_1;
    int uVar2 = 0, iVar3 = 0, uVar4 = 0;
    volatile int *piVar1 = (volatile int*)0x200024f0UL;

    if (uVar5 < 6) {
        if (*piVar1 != 1) {
            FUN_00043308();
            *piVar1 = 1;
            uVar2 = FUN_0007d3ee();
            iVar3 = FUN_0007d446();
            FUN_00043324(uVar2, iVar3+0x36);
            iVar3 = FUN_000167a8();
            uVar2 = *(int*)(iVar3+0xeb4);
            iVar3 = FUN_000167a8();
            FUN_00047260(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
        }
        uVar2 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar3 = iVar3+0x36;
        uVar4 = 1;
    } else if (uVar5 == 6) {
        if (*piVar1 != 9) {
            FUN_00043308();
            *piVar1 = 9;
            uVar2 = FUN_0007d3ee();
            iVar3 = FUN_0007d446();
            FUN_00043324(uVar2, iVar3+0x36);
            iVar3 = FUN_000167a8();
            uVar2 = *(int*)(iVar3+0xeb4);
            iVar3 = FUN_000167a8();
            FUN_00047260(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
        }
        uVar2 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar3 = iVar3+0x36;
        uVar4 = 9;
    } else {
        if (uVar5 != 7) {
            if (uVar5 < 0xc) {
                if (*piVar1 == 0xff) return 0;
                FUN_00043308();
                *piVar1 = 0xff;
                uVar2 = FUN_0007d3ee();
                iVar3 = FUN_0007d446();
                FUN_00043324(uVar2, iVar3+0x36);
                iVar3 = FUN_000167a8();
                uVar2 = *(int*)(iVar3+0xeb4);
                iVar3 = FUN_000167a8();
                FUN_00047260(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
                return 0;
            }
            if (uVar5-0xc < 2) return 0;
            if (uVar5==0xf) return 0;
            if ((uVar5!=0xe) && (uVar5!=0x10)) return 0;
            if (*piVar1==0xff) return 0;
            FUN_00043308();
            *piVar1 = 0xff;
            return 0;
        }
        if (*piVar1 != 4) {
            FUN_00043308();
            *piVar1 = 4;
            uVar2 = FUN_0007d3ee();
            iVar3 = FUN_0007d446();
            FUN_00043324(uVar2, iVar3+0x36);
            iVar3 = FUN_000167a8();
            uVar2 = *(int*)(iVar3+0xeb4);
            iVar3 = FUN_000167a8();
            FUN_00047260(uVar2, *(int*)(iVar3+0xeb8), 0,0,0x280,199);
        }
        uVar2 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar3 = iVar3+0x36;
        uVar4 = 4;
    }
    FUN_0004334c(uVar4,uVar2,iVar3,0,0,0,0,param_4);
    return 0;
}

