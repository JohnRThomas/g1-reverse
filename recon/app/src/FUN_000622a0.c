/* Reconstructed FUN_000622a0 @ 0x622a0  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int fmt, ...);
extern int FUN_0007f998(int a0,int a1);
extern int FUN_0007f9c6(int a0,int a1);
extern int FUN_0007f9f4(int a0,int a1);
extern int FUN_0007fa22(int a0,int a1);
extern int FUN_0007fa7a(int a0,int a1);
extern int FUN_0007fb20(int a0,int a1,int a2,void *a3,int a4);
extern int FUN_0007fb3e(int a0,int a1);
extern int FUN_0007fb4c(int a0,int a1);
extern int FUN_0007fb7a(int a0,int a1);
extern int FUN_0007fbd6(int a0,int a1);
extern int FUN_0007fc72(int a0,int a1);
extern int FUN_0007fd4e(int a0,int a1);
extern int FUN_0007fe2a(int a0,int a1);
extern int FUN_0007fe72(int a0,int a1);
extern void FUN_00086384(int a0);

int FUN_000622a0(int param_1, unsigned int param_2, int param_3)
{
    int *piVar6, iVar7, iVar8, iVar2, iVar10;
    unsigned int uVar3, uVar5;
    signed char cVar4;
    unsigned short uVar9;
    int bVar11;
    unsigned int uStack_24;

    piVar6 = *(int**)(param_1+0x10);
    *piVar6 = param_1;
    iVar7 = *(int*)(param_1+4);
    iVar8 = *(int*)(param_1+0x10);
    uStack_24 = param_2;

    iVar2 = FUN_0007fb20(iVar7, 0, param_3, piVar6, param_1);
    uVar3 = 0x000f6292;
    if (iVar2 < 0) goto LAB_622bc;
    iVar2 = FUN_0007fb3e(iVar7, ((int)&uStack_24) + 2);
    uVar3 = 0x000f62ac;
    if (iVar2 < 0) goto LAB_622bc;

    DEBUG_PRINT(0x000f62c5, (param_2 >> 0x10) & 0xff);
    uVar5 = (param_2 >> 0x10) & 0xff;
    uVar3 = 0x000f62e6;
    if (uVar5 == 0x6c) {
        iVar2 = FUN_0007fb7a(iVar7, 0x80);
        uVar3 = 0x000f62fd;
        if (iVar2 < 0) goto LAB_622bc;
        iVar2 = FUN_0007fe72(iVar7, ((int)&uStack_24) + 3);
        uVar3 = 0x000f6315;
        if (iVar2 < 0) goto LAB_622bc;
        if (((param_2 >> 0x18) & 0xff) != 0) {
            DEBUG_PRINT(0x000f6337);
            FUN_0007fe2a(iVar7, 0);
            FUN_00086384(300);
        }
        iVar2 = FUN_0007fb4c(iVar7, 1);
        if (iVar2 < 0) goto LAB_622ec;
        FUN_00086384(100);
        DEBUG_PRINT(0x000f6353, (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x18));
        cVar4 = *(volatile signed char*)(iVar7+0x18);
        if ((cVar4 != 1) && (cVar4 != 2)) cVar4 = 0;
        FUN_0007fa22(iVar7, cVar4);
        uVar5 = (*(volatile unsigned char*)(iVar7+0x1a)) & 0x3f;
        DEBUG_PRINT(0x000f6364, uVar5);
        iVar10 = *(int*)(param_1+0x10);
        iVar2 = FUN_0007f998(*(int*)(param_1+4), uVar5);
        uVar3 = 0x000f6378;
        if (iVar2 >= 0) {
            *(volatile unsigned char*)(iVar10+0x1e) = (unsigned char)uVar5;
            uVar3 = 0x000f639f;
            bVar11 = (*(volatile signed char*)(iVar7+0x1a)) >= 0;
            {
                unsigned short tbl = *(volatile unsigned short*)(0x0009905eUL + (unsigned int)uVar5*2);
                unsigned long long lVar1;
                unsigned int newv;
                if (bVar11) {
                    lVar1 = (unsigned long long)tbl * 0x3d;
                    newv = (unsigned int)(lVar1 >> 1);
                } else {
                    lVar1 = (((unsigned long long)0x3d) << 32) | (unsigned long long)tbl;
                    newv = (unsigned int)(lVar1 >> 32) * (unsigned int)lVar1;
                }
                *(volatile unsigned int*)(iVar8+0xc) = newv;
            }
            uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x19);
            DEBUG_PRINT(uVar3, uVar5);
            if (uVar5 > 10) {
                iVar10 = 0x1a04;
            }
            uVar9 = (unsigned short)iVar10;
            if (uVar5 < 0xb) {
                uVar9 = *(volatile unsigned short*)(0x00099066UL + (unsigned int)uVar5*2);
            }
            *(volatile unsigned short*)(iVar8+0x1c) = uVar9;
            iVar10 = *(int*)(param_1+0x10);
            iVar2 = FUN_0007fc72(*(int*)(param_1+4), uVar5);
            uVar3 = 0x000f63c1;
            if (iVar2 >= 0) {
                *(volatile unsigned short*)(iVar10+0x1c) = uVar9;
                DEBUG_PRINT(0x000f63b1, (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1b));
                cVar4 = *(volatile signed char*)(iVar7+0x1b);
                if (cVar4 != 1) cVar4 = 0;
                FUN_0007fa7a(iVar7, cVar4);
                uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1d);
                DEBUG_PRINT(0x000f63e6, uVar5);
                iVar2 = FUN_0007f9c6(*(int*)(param_1+4), uVar5);
                uVar3 = 0x000f63f9;
                if (iVar2 >= 0) {
                    *(volatile unsigned int*)(iVar8+0x18) = (unsigned int)(*(volatile unsigned short*)(0x00099042UL + (unsigned int)uVar5*2)) * 0x1117;
                    uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1c);
                    DEBUG_PRINT(0x000f641c, uVar5);
                    if (uVar5 < 0xb) {
                        uVar9 = *(volatile unsigned short*)(0x00099066UL + (unsigned int)uVar5*2);
                    } else {
                        uVar9 = 0x1a04;
                    }
                    *(volatile unsigned short*)(iVar8+0x20) = uVar9;
                    iVar2 = FUN_0007fd4e(*(int*)(param_1+4), uVar5);
                    uVar3 = 0x000f642d;
                    if (iVar2 >= 0) {
                        iVar2 = FUN_0007fbd6(iVar7, 0);
                        uVar3 = 0x000f644e;
                        if (iVar2 >= 0) {
                            iVar2 = FUN_0007f9f4(iVar7, 1);
                            uVar3 = 0x000f6468;
                            if (iVar2 >= 0) {
                                return 0;
                            }
                        }
                        goto LAB_622bc;
                    }
                }
            }
        }
    } else {
        uVar3 = 0x000f62e6;
    }
    DEBUG_PRINT(uVar3, uVar5);
    goto LAB_622ec;
LAB_622bc:
    DEBUG_PRINT(uVar3);
LAB_622ec:
    DEBUG_PRINT(0x000f6481);
    return 0;
}

