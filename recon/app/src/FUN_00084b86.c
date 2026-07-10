/* Reconstructed FUN_00084b86 @ 0x84b86  (parity: 300/300 trials, PROVEN) */

extern void FUN_0008484e(int a,int b,int c,int d,unsigned e);
extern void FUN_0008673e(int a);
void FUN_00084b86(int param_1, unsigned p2, unsigned p3, unsigned param_4){
    int piVar6 = *(volatile int*)(param_1 + 0x34);
    if (*(volatile signed char*)(*(volatile int*)(piVar6+0xc) + 0xce) != 0) return;
    int iVar7 = *(volatile int*)(piVar6+0);
    *(volatile int*)(*(volatile int*)(*(volatile int*)(iVar7+4)) + 0x308) = 0x10;
    int node = *(volatile int*)(piVar6+0xc);
    int iVar3v = *(volatile int*)(node + 0xb8);
    int bVar8 = (*(volatile int*)(node + 0x6c) != iVar3v);
    if (bVar8){
        *(volatile int*)(node + 0x6c) = iVar3v;
        node = *(volatile int*)(piVar6+0xc);
        iVar3v = *(volatile int*)(node + 0x74);
        *(volatile int*)(node + 0x7c) = iVar3v;
    }
    int iv3 = *(volatile int*)(piVar6+0xc);
    int iVar5 = *(volatile int*)(iv3 + 0x6c) - *(volatile int*)(iv3 + 0x70);
    int iVar4 = 0;
    if (iVar5 < 0){
        *(volatile int*)(iv3 + 0xb8) = *(volatile int*)(iv3 + 0x70);
        iv3 = *(volatile int*)(piVar6+0xc);
        unsigned uVar1 = *(volatile unsigned*)(iv3 + 0x5c);
        unsigned uVar2 = *(volatile unsigned*)(iv3 + 0x60);
        if (uVar2 <= uVar1) goto LAB;
        iVar4 = iVar5;
        iVar5 = (int)(uVar1 - uVar2);
        if (iVar5 <= 0) goto LAB;
        bVar8 = 1;
    } else {
        unsigned uVar1 = *(volatile unsigned*)(iv3 + 0x5c);
        unsigned uVar2 = *(volatile unsigned*)(iv3 + 0x60);
        if ((unsigned)((unsigned)iVar5 + uVar2) > uVar1){
            iVar4 = iVar5;
            iVar5 = (int)(uVar1 - uVar2);
            if (iVar5 <= 0) goto LAB;
            bVar8 = 1;
        } else {
            if (iVar5 == 0) goto LAB;
            iVar4 = *(volatile int*)(iv3 + 0x7c);
            bVar8 = 0;
            if (*(volatile int*)(iv3 + 0x78) <= iVar4){
                *(volatile int*)(iv3 + 0x7c) = iVar4 - *(volatile int*)(iv3 + 0x78);
                goto LAB;
            }
        }
    }
    FUN_0008484e(iVar7, iVar5, iVar4, iv3, param_4);
    { int n = *(volatile int*)(piVar6+0xc);
      *(volatile int*)(n + 0x60) = *(volatile int*)(n + 0x60) + iVar5; }
    { int n = *(volatile int*)(piVar6+0xc);
      *(volatile int*)(n + 0x70) = *(volatile int*)(n + 0x70) + iVar5; }
    if (bVar8){
        int n = *(volatile int*)(piVar6+0xc);
        FUN_0008673e(n + 0x80);
    }
LAB:
    *(volatile int*)(*(volatile int*)(*(volatile int*)(iVar7+4)) + 0x304) = 0x10;
    return;
}

