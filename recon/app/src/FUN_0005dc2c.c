/* Reconstructed FUN_0005dc2c @ 0x5dc2c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00056a68(unsigned a, int b);
extern void FUN_0005daf0(int a, unsigned b);
extern void FUN_0005f24c(int a);
extern unsigned FUN_0005f5d0(int a, int b);
extern int FUN_00081820(unsigned a, int b, int c, int d, int e);
extern unsigned FUN_00082ff6(int a, int b);
extern void FUN_00083074(unsigned a, unsigned b, void*c);
extern int FUN_000830b0(int a, int b);
unsigned FUN_0005dc2c(int param_1, unsigned param_2){
    int iVar4 = param_1 + 4;
    unsigned uVar1 = FUN_00082ff6(iVar4, 2);
    if (uVar1 != 0) uVar1 = (*(volatile short*)(param_1 + 0xe8) == 0) ? 1 : 0;
    int called = 0;
    if (FUN_00082ff6(iVar4, 3) != 0) called = 1;
    else if (FUN_00082ff6(iVar4, 1) != 0) called = 1;
    else if (FUN_00082ff6(iVar4, 0xf) != 0) called = 1;
    if (called) FUN_0005daf0(param_1, param_2);
    unsigned loc[4];
    if (uVar1 == 0){
        int node = FUN_000830b0(param_1, 5);
        if (node == 0) return 0xffffff97u;
        unsigned char *puVar3 = (unsigned char*)FUN_0005f5d0(node + 0xc, 1);
        *(volatile unsigned char*)puVar3 = (unsigned char)param_2;
        int i = FUN_00081820(*(volatile unsigned*)(param_1 + 0xf0), 6, node, 0, 0);
        if (i != 0) FUN_0005f24c(node);
    } else {
        loc[1] = 0x000f4f98; loc[0] = 2;
        FUN_00083074(0x00088180, 0x1080, loc);
        FUN_00056a68(*(volatile unsigned*)(param_1 + 0xf0), 5);
    }
    return 0;
}

