/* Reconstructed FUN_0005e1a8 @ 0x5e1a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned undefined4;
extern unsigned int FUN_00052cdc(const void *);
extern int FUN_00054250(int a);
extern int FUN_00055cb4(void *, int);
extern void FUN_0005cb38(int *a, int b, unsigned c);
extern void FUN_0005daf0(int *a, unsigned char b);
extern void FUN_0005e9a0(int a, int b);
extern int FUN_0005f5d0(int a, int b);
extern int FUN_00082ff6(int *a, int b);
extern void FUN_00083074(unsigned a, int b, void *c);
extern unsigned FUN_00083090(int a, unsigned b);
extern int FUN_000830b0(int *a, int b);
extern int FUN_000831be(int *a, int b);
extern void FUN_00083204(int *a);
extern void FUN_00086c04(int a, void *b, unsigned c);
extern void FUN_00086c78(int a, int b, int c);

void FUN_0005e1a8(int *param_1, int param_2)
{
    int iVar1, iVar3, iVar11;
    uint uVar2;
    undefined2 *puVar4;
    unsigned uVar5, uVar6;
    unsigned *puVar7, *puVar12;
    undefined1 uVar8;
    int *piVar9, *piVar10;
    undefined4 local_70, local_6c, uStack_68;
    undefined2 local_64;
    undefined4 local_50, local_4c;
    undefined4 local_44[4];
    undefined4 local_34, uStack_30;
    undefined2 local_2c;

    piVar10 = param_1 + -0x3b;
    piVar9 = param_1 + -0x3c;
    iVar11 = *param_1;
    iVar1 = FUN_000831be(piVar10, 1);
    if (iVar1 == 0) return;
    if (param_2 != 0) {
        iVar1 = FUN_00082ff6(piVar10, 3);
        if (iVar1 == 0) return;
        iVar1 = FUN_00054250(param_2);
        uVar2 = iVar1 - 1U & 0xff;
        if (uVar2 < 9) uVar8 = *(volatile undefined1 *)(0xf5217 + uVar2);
        else uVar8 = 0;
        FUN_00083090((int)piVar10, 2);
        goto LAB_0005e1fa;
    }
    if (*(volatile char *)(iVar11 + 0xb) == '\0') return;
    iVar1 = FUN_00082ff6(piVar10, 3);
    if (iVar1 == 0) {
        FUN_00083204(piVar9);
        return;
    }
    iVar1 = FUN_00082ff6(piVar10, 5);
    if (iVar1 != 0) {
        if (((int)((uint)*(volatile unsigned char *)((int)param_1 - 8) << 0x1c) < 0) &&
            ((int)((uint)*(volatile unsigned char *)((int)param_1 - 7) << 0x1c) < 0)) {
            FUN_00083090((int)piVar10, 0x11);
        }
        *(volatile unsigned char *)((int)param_1 - 8) &= 0xf7;
        *(volatile unsigned char *)((int)param_1 - 7) &= 0xf7;
    }
    uVar2 = (uint)*(volatile unsigned char *)((int)param_1 - 7);
    if ((int)(uVar2 << 0x1f) < 0) {
        uVar5 = 6;
LAB_0005e264:
        FUN_00083090((int)piVar9, uVar5);
    } else {
        if ((int)(uVar2 << 0x1e) < 0) {
            uVar5 = 8;
            goto LAB_0005e264;
        }
        if ((int)(uVar2 << 0x1d) < 0) {
            uVar5 = 10;
            goto LAB_0005e264;
        }
    }
    uVar5 = FUN_00083090((int)piVar10, 2);
    if (*(volatile int *)(*param_1 + 0xc0) == 0) {
        uStack_68 = FUN_00052cdc(*param_1 + 0x90);
        local_6c = 0xf516d;
        local_64 = 0x200;
        local_70 = 0x01000003;
        FUN_00083074(0x88180, 0x1c40, &local_70);
        return;
    }
    iVar1 = FUN_00082ff6((int *)uVar5, 5);
    if ((iVar1 == 0) && ((int)((uint)*(volatile unsigned char *)((int)param_1 - 8) << 0x1f) < 0)) {
        iVar11 = *(volatile int *)(*param_1 + 0xc0);
        iVar1 = FUN_00055cb4(local_44, 0x1a);
        uVar5 = 0xf5182;
        if ((iVar1 == 0) && (iVar1 = FUN_000830b0(piVar9, 6), uVar5 = 0xf519d, iVar1 != 0)) {
            iVar3 = FUN_0005f5d0(iVar1 + 0xc, 0x10);
            FUN_00086c04(iVar3, local_44, *(volatile unsigned char *)(iVar11 + 0xc));
            uVar2 = (uint)*(volatile unsigned char *)(iVar11 + 0xc);
            if (uVar2 < 0x10) {
                FUN_00086c78(uVar2 + iVar3, 0, 0x10 - uVar2);
            }
            FUN_0005cb38(piVar9, iVar1, 0);
            iVar1 = FUN_000830b0(piVar9, 7);
            uVar5 = 0xf51c4;
            if (iVar1 != 0) {
                puVar4 = (undefined2 *)FUN_0005f5d0(iVar1 + 0xc, 10);
                *(undefined4 *)(puVar4 + 1) = local_34;
                *(undefined4 *)(puVar4 + 3) = uStack_30;
                *puVar4 = local_2c;
                FUN_0005cb38(piVar9, iVar1, 0x5e41d);
                iVar1 = FUN_00082ff6(piVar10, 0xd);
                if (iVar1 != 0) {
                    FUN_0005e9a0(iVar11, 1);
                    puVar7 = local_44;
                    puVar12 = (unsigned *)(iVar11 + 0x4a);
                    do {
                        uVar5 = *puVar7;
                        uVar6 = puVar7[1];
                        puVar7 = puVar7 + 2;
                        *puVar12 = uVar5;
                        puVar12[1] = uVar6;
                        puVar12 = puVar12 + 2;
                    } while (puVar7 != &local_34);
                    *(undefined4 *)(iVar11 + 0x40) = local_34;
                    *(undefined4 *)(iVar11 + 0x44) = uStack_30;
                    *(undefined2 *)(iVar11 + 0x48) = local_2c;
                }
                goto LAB_0005e2f2;
            }
        }
        local_50 = 2;
        local_4c = uVar5;
        FUN_00083074(0x88180, 0x1040, &local_50);
    }
LAB_0005e2f2:
    if ((short)param_1[-2] != 0) return;
    uVar8 = 0;
LAB_0005e1fa:
    FUN_0005daf0(piVar9, uVar8);
    return;
}

