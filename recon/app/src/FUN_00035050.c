/* Reconstructed FUN_00035050 @ 0x35050  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern void FUN_00019c70(unsigned, ...);
extern int FUN_00034ff0(void *a, void *b);
extern void FUN_00064b1c(int a);
extern int FUN_0008500c(void);
extern int FUN_00085020(int a);
extern int FUN_00085030(int a, uint b);
extern int FUN_0008503c(int a, unsigned b);
extern int FUN_000850c8(void);
extern void FUN_0008705a(void *a, unsigned b, int c);

undefined4 FUN_00035050(void)
{
    volatile int *dbgp = (volatile int *)0x20007554;
    volatile unsigned char *pbVar2 = (volatile unsigned char *)0x2001a22c;
    int *piVar1;
    unsigned char bVar3;
    int iVar4, iVar5, iVar6, iVar7;
    undefined4 uVar8;
    uint uVar9, uVar10, uVar11;
    unsigned char auStack_60[15], local_51, auStack_50[39], local_29;

    iVar4 = FUN_0008500c();
    if (iVar4 == 0) {
        if (*dbgp == 0) DEBUG_PRINT(0xa8762);
        else FUN_00019c70(0);
        return 0;
    }
    iVar5 = FUN_0008503c(iVar4, 0xa862c);
    if (iVar5 == 0) {
        iVar5 = *dbgp;
        uVar8 = 0xa8638;
LAB_00035088:
        if (iVar5 == 0) DEBUG_PRINT(uVar8);
        else FUN_00019c70(0);
    } else {
        if ((int)((*pbVar2 & 1)) != (*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa877a;
            goto LAB_00035088;
        }
        iVar5 = FUN_0008503c(iVar4, 0xa864e);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa8659;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1e) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8798;
            goto LAB_00035088;
        }
        iVar5 = FUN_0008503c(iVar4, 0xa866e);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa87b5;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1c) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa87d3;
            goto LAB_00035088;
        }
        iVar5 = FUN_0008503c(iVar4, 0xa869b);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa87f5;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1d) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8812;
            goto LAB_00035088;
        }
        iVar5 = FUN_0008503c(iVar4, 0x9e1b6);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86c8;
            goto LAB_00035088;
        }
        iVar6 = FUN_0008503c(iVar5, 0x9e235);
        if (iVar6 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86db;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1b) >> 0x1f != (uint)(*(volatile int *)(iVar6 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8833;
            goto LAB_00035088;
        }
        iVar5 = FUN_0008503c(iVar5, 0xf3630);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86f4;
            goto LAB_00035088;
        }
        iVar6 = FUN_000850c8();
        if (iVar6 != 0) {
            bVar3 = FUN_00085020(iVar5);
            piVar1 = (int *)0x20007554;
            uVar9 = (uint)bVar3;
            if (pbVar2[1] != uVar9) {
                iVar5 = *dbgp;
                uVar8 = 0xa8850;
                goto LAB_00035088;
            }
            uVar11 = 0;
            for (uVar10 = uVar11; (uVar10 & 0xff) < uVar9; uVar10 = uVar10 + 1) {
                iVar6 = FUN_00085030(iVar5, uVar10);
                if (iVar6 == 0) {
                    iVar6 = *piVar1;
                    uVar8 = 0xa870b;
LAB_000351c4:
                    if (iVar6 == 0) DEBUG_PRINT(uVar8);
                    else FUN_00019c70(0);
                } else {
                    iVar7 = FUN_0008503c(iVar6, 0x9a1dd);
                    if (iVar7 == 0) {
                        iVar6 = *piVar1;
                        uVar8 = 0xa8724;
                        goto LAB_000351c4;
                    }
                    iVar6 = FUN_0008503c(iVar6, 0xf33e4);
                    if (iVar6 == 0) {
                        iVar6 = *piVar1;
                        uVar8 = 0xa8739;
                        goto LAB_000351c4;
                    }
                    local_29 = 0;
                    local_51 = 0;
                    FUN_0008705a(auStack_50, *(volatile undefined4 *)(iVar7 + 0x10), 0x27);
                    FUN_0008705a(auStack_60, *(volatile undefined4 *)(iVar6 + 0x10), 0xf);
                    iVar6 = FUN_00034ff0(auStack_50, auStack_60);
                    if (iVar6 == 0) break;
                    uVar11 = uVar11 + 1 & 0xff;
                }
            }
            if (uVar11 == uVar9) {
                if (*dbgp == 0) DEBUG_PRINT(0xa886d);
                else FUN_00019c70(0);
                uVar8 = 1;
                goto LAB_0003523e;
            }
        }
    }
    uVar8 = 0;
LAB_0003523e:
    FUN_00064b1c(iVar4);
    if (*dbgp == 0) DEBUG_PRINT(0xa8884, uVar8);
    else FUN_00019c70(0);
    return uVar8;
}

