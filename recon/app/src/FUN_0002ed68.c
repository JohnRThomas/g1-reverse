/* Reconstructed FUN_0002ed68 @ 0x2ed68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern void FUN_00019c70(unsigned, ...);
extern void FUN_0002ec5c(int a);
extern void FUN_0002f6b0(int a);
extern int FUN_00032ee4(void);
extern void FUN_0004a4d0(void *a);
extern unsigned FUN_00060f20(void);
extern int FUN_00068e40(int a, int b);
extern unsigned FUN_00068ecc(int a, int b);
extern unsigned FUN_00068f94(int a, int b, int c, int d);
extern int FUN_00069238(unsigned a, int b, int c, int d, int e, int f, unsigned g, int h);
extern int FUN_00076d6c(unsigned a);
extern void FUN_00076d7c(int a);
extern int FUN_0008638c(int a);

void FUN_0002ed68(int param_1, int param_2)
{
    volatile int *v = (volatile int *)0x2000230c;
    volatile int *dbg = (volatile int *)0x20007554;
    volatile int *S = (volatile int *)0x00087bf0;
    volatile uint *puVar2v = (volatile uint *)0x20002404;
    int *piVar1;
    uint *puVar2;
    unsigned uVar3;
    uint uVar4;
    int iVar5, iVar6, iVar7, iVar8, iVar9, iVar10, iVar11;
    unsigned local_30, uStack_2c;

    uVar3 = FUN_00068ecc(10000, 16000);
    uVar4 = FUN_00068e40(10000, 16000);
    iVar5 = FUN_00076d6c(uVar3);
    iVar11 = (uVar4 & 0x7fff) * 2;
    iVar6 = FUN_00076d6c(iVar11);
    iVar10 = (param_2 / iVar11 & 0xffffU) * 0x14;
    iVar7 = FUN_00076d6c(iVar10);
    if (iVar5 == 0) {
        if (0 < *v) {
            if (*dbg == 0) DEBUG_PRINT(0xa3f7f, 0xa41c2);
            else FUN_00019c70(0);
        }
LAB_0002edf8:
        iVar5 = iVar6;
        if (iVar6 != 0) goto LAB_0002ede2;
    } else {
        if (iVar6 != 0) {
            if (iVar7 != 0) {
                iVar8 = FUN_00032ee4();
                piVar1 = (int *)S;
                if ((iVar8 == 1) && (iVar8 = FUN_0008638c(0x87bf0), iVar8 == 0)) {
                    if (0 < *v) {
                        iVar9 = *piVar1;
                        iVar10 = *dbg;
                        uVar3 = 0x9e9ea;
LAB_0002ee5a:
                        if (iVar10 == 0) DEBUG_PRINT(uVar3, 0xa41c2, iVar9);
                        else FUN_00019c70(0);
                    }
                } else {
                    uVar3 = FUN_00068f94(10000, 16000, 0, iVar5);
                    iVar8 = iVar7;
                    do {
                        if (iVar8 == iVar10 + iVar7) {
                            iVar11 = FUN_00032ee4();
                            puVar2 = (uint *)puVar2v;
                            if (iVar11 != 1) {
                                if (*(volatile int *)0x20007b78 == 0) {
                                    FUN_0002ec5c(iVar7);
                                } else {
                                    local_30 = 0;
                                    uStack_2c = 0;
                                    FUN_0004a4d0(&local_30);
                                    if (2 < *v) {
                                        if (*dbg == 0) DEBUG_PRINT(0xa3fdf, 0xa41c2, local_30, uStack_2c);
                                        else FUN_00019c70(0xa3fdf, 0xa41c2);
                                    }
                                    FUN_0002f6b0(iVar7);
                                }
                                goto LAB_0002eeb6;
                            }
                            if (0x40ffff < *puVar2v) goto LAB_0002eeb6;
                            iVar9 = (**(int (***)(int, uint, int, int))(*(volatile int *)(0x87bf0 + 8) + 4))(0x87bf0, *puVar2v, iVar7, iVar10);
                            if (iVar9 != 0) {
                                if (*v < 1) goto LAB_0002eeb6;
                                iVar10 = *dbg;
                                uVar3 = 0x9ebc6;
                                goto LAB_0002ee5a;
                            }
                            if (0 < *v) {
                                if (*dbg == 0) DEBUG_PRINT(0xa3fbe, 0xa41c2, *puVar2);
                                else FUN_00019c70(0);
                            }
                            *puVar2 = *puVar2 + iVar10;
                            goto LAB_0002eeb6;
                        }
                        iVar9 = FUN_00069238(uVar3, 0, param_1, 1, 0x14, iVar8, uVar3, param_1);
                        iVar8 = iVar8 + 0x14;
                        param_1 = param_1 + iVar11;
                    } while (iVar9 == 0);
                    if (0 < *v) {
                        iVar10 = *dbg;
                        uVar3 = 0xa3f95;
                        goto LAB_0002ee5a;
                    }
                }
LAB_0002eeb6:
                FUN_00076d7c(iVar5);
                FUN_00076d7c(iVar6);
                goto LAB_0002edce;
            }
            if (*v < 1) {
                FUN_00076d7c(iVar5);
                iVar7 = iVar6;
                goto LAB_0002edce;
            }
LAB_0002ee16:
            if (*dbg == 0) DEBUG_PRINT(0xa3f7f, 0xa41c2);
            else FUN_00019c70(0);
            FUN_00076d7c(iVar5);
            goto LAB_0002edf8;
        }
        if (0 < *v) goto LAB_0002ee16;
LAB_0002ede2:
        FUN_00076d7c(iVar5);
    }
    if (iVar7 == 0) return;
LAB_0002edce:
    FUN_00076d7c(iVar7);
    return;
}

