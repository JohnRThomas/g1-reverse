/* Reconstructed FUN_00054260 @ 0x54260  (parity: 300/300 trials, PROVEN) */

extern int FUN_00054250(int a);
extern void FUN_000566a4(int a);
extern int FUN_00056908(unsigned a, int b);
extern void FUN_00056a68(int a, int b);
extern void FUN_00056da8(int a, int b, int c);
extern void FUN_0005e47c(void);
extern int FUN_00080e38(int a);
extern void FUN_00080ea2(unsigned a, unsigned b, void*c);
void FUN_00054260(int param_1){
    char *p = *(char**)(param_1 + 0xc);
    unsigned uVar5 = *(volatile unsigned short*)(p + 1);
    unsigned cVar1 = *(volatile unsigned char*)p;
    int iVar2 = FUN_00056908(uVar5, 0xf);
    unsigned loc[4];
    if (iVar2 == 0){
        loc[1] = 0x000f2e3c; loc[0]=3; loc[2]=uVar5;
        FUN_00080ea2(0x00088138, 0x1840, loc);
        return;
    }
    if (cVar1 == 0 && *(volatile unsigned char*)(iVar2 + 2) == 1){
        FUN_0005e47c();
        int iVar4 = FUN_00080e38(iVar2);
        if (iVar4 == 0){
            int u = FUN_00054250(5);
            FUN_00056da8(iVar2, 5, u);
            loc[1] = 0x000f30dd; loc[0]=2;
            FUN_00080ea2(0x00088138, 0x1040, loc);
            FUN_00056a68(iVar2, 5);
            FUN_000566a4(iVar2);
            return;
        }
    }
    int u = FUN_00054250((int)cVar1);
    FUN_00056da8(iVar2, (int)cVar1, u);
    FUN_000566a4(iVar2);
    return;
}

