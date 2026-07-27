/* Reconstructed FUN_00033d58 @ 0x33d58  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(int,...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00033cf8(int,...);
extern unsigned FUN_0007d224(int,...);
extern int FUN_00086c04(int,...);
extern int FUN_00086c78(int,...);

void FUN_00033d58(int param_1)
{
    int iVar2 = 0x20007dac;
    int iVar5, iVar7, iVar8, iVar9, iVar10, iVar11;
    unsigned uVar6;
    unsigned char uVar4;
    int local_2c;

    iVar10 = 0; iVar11 = 0; iVar9 = 0;
    *(volatile unsigned char *)0x20018d8eUL = 1;
LAB_00033d76:
    iVar5 = *(volatile int *)(iVar2 + iVar9 * 0x1b4);
    iVar7 = iVar2 + iVar9 * 0x1b4;
    iVar8 = *(volatile int *)(iVar7 + 4);
    if (iVar5 == 0) {
        if (iVar10 == 0) goto LAB_00033dc2;
        if (iVar11 == 0) {
            iVar11 = iVar10;
            if (iVar8 == 0) {
                iVar7 = iVar9 + 1;
                goto joined_00033edc;
            }
            if (*(volatile char *)(iVar7 + 0xf) == 0) goto LAB_00033daa;
LAB_00033de4:
            if (param_1 != 0) goto LAB_00033e20;
LAB_00033de8:
            uVar6 = FUN_0007d224(0);
            iVar5 = iVar2 + iVar9 * 0x1b4;
            if (uVar6 <= (unsigned)(*(volatile int *)(iVar5 + 4) + 10)) goto LAB_00033daa;
        } else {
            if (*(volatile char *)(iVar7 + 0xf) == 0) {
LAB_00033d92:
                iVar7 = iVar9 + iVar11;
joined_00033edc:
                if (iVar7 < 10) goto LAB_00033e98;
                goto LAB_00033e3e;
            }
            if (param_1 == 0) {
                if (iVar8 == 0) goto LAB_00033d92;
                goto LAB_00033de8;
            }
            if (iVar8 == 0) goto LAB_00033d92;
LAB_00033e20:
            iVar5 = iVar2 + iVar9 * 0x1b4;
        }
        local_2c = iVar9 * 0x1b4;
        iVar11 = iVar11 + 1;
        iVar7 = iVar11 + iVar9;
        FUN_00086c78(iVar5, 0, 0x1b4);
        if (9 < iVar7) goto LAB_00033e3e;
        if (*(volatile int *)(iVar2 + local_2c) != 0) {
            iVar9 = iVar9 + 1;
            goto LAB_00033d76;
        }
    } else {
        iVar10 = 1;
LAB_00033dc2:
        if (iVar8 == 0) {
            if (iVar11 != 0) {
                iVar7 = iVar9 + iVar11;
                if (9 < iVar7) goto LAB_00033e3e;
                if (iVar5 == 0) goto LAB_00033e98;
LAB_00033e8a:
                iVar9 = iVar9 + 1;
                goto LAB_00033d76;
            }
            goto LAB_00033dc8;
        }
        iVar8 = iVar2 + iVar9 * 0x1b4;
        if (*(volatile char *)(iVar8 + 0xf) != 0) goto LAB_00033de4;
        if ((iVar5 != 0) && (uVar6 = FUN_0007d224(0), (unsigned)(*(volatile int *)(iVar8 + 4) + 5) < uVar6)) {
            iVar11 = iVar11 + 1;
            iVar7 = iVar11 + iVar9;
            FUN_00086c78(iVar8, 0, 0x1b4);
            if (iVar7 < 10) {
                if (*(volatile int *)(iVar2 + iVar9 * 0x1b4) != 0) goto LAB_00033e8a;
                goto LAB_00033e98;
            }
            goto LAB_00033e3e;
        }
LAB_00033daa:
        iVar7 = iVar11 + iVar9;
        if (9 < iVar7) goto LAB_00033e3e;
        if ((*(volatile int *)(iVar2 + iVar9 * 0x1b4) != 0) || (iVar11 == 0)) goto LAB_00033dc8;
    }
LAB_00033e98:
    iVar5 = iVar7 * 0x1b4 + iVar2;
    if (*(volatile char *)(iVar5 + 0x10) == 0) {
        iVar11 = iVar11 + 1;
        goto LAB_00033d76;
    }
    FUN_00086c04(iVar2 + iVar9 * 0x1b4, iVar5, 0x1b4);
    FUN_00086c78(iVar5, 0, 0x1b4);
    if (0 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a7d87, 0x000a8265, iVar7, iVar9);
        } else {
            FUN_00019c70(0x000a7d87, 0x000a8265, iVar7, iVar9);
        }
    }
LAB_00033dc8:
    iVar9 = iVar9 + 1;
    if (iVar9 == 10) {
LAB_00033e3e:
        iVar11 = FUN_000167a8(0);
        uVar4 = (unsigned char)FUN_00033cf8(0);
        *(volatile unsigned char *)(iVar11 + 0xdd) = uVar4;
        *(volatile unsigned char *)0x20018d8eUL = 0;
        return;
    }
    goto LAB_00033d76;
}
