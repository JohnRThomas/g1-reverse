/* Reconstructed FUN_00065b9c @ 0x65b9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint64_t FUN_00065434(void);
extern void FUN_000654c4(void);
extern int FUN_00065584(void);
extern int FUN_00065620(void);
extern void FUN_000851ca(void);

void FUN_00065b9c(void)
{
    int uVar6 = FUN_00065620();
    int local_30[3];

    if (uVar6 < 0) {
        int iVar13;
        int *piVar12;
        local_30[0] = *(volatile int*)0x50842520; *(volatile int*)0x50842520 = local_30[0];
        local_30[1] = *(volatile int*)0x50842820; *(volatile int*)0x50842820 = local_30[1];
    LAB_bce:
        iVar13 = 0;
        piVar12 = local_30;
        while (1) {
            volatile uint8_t *pbVar14 = (volatile uint8_t*)(iVar13 + 0x000f6bb7);
            int iVar8;
            while ((iVar8 = piVar12[0]) != 0) {
                unsigned uVar10 = __builtin_ctz((unsigned)iVar8) | ((unsigned)*pbVar14 << 5);
                uint64_t uVar16 = FUN_00065434();
                unsigned uVar11 = (unsigned)(uVar16 >> 32);
                uint16_t uVar1 = *(volatile uint16_t*)(0x20002bc0 + ((int)uVar16 + 8) * 2);
                unsigned uVar7 = uVar11 >> 3;
                *(volatile uint8_t*)((int)(intptr_t)piVar12 + uVar7) &=
                    (uint8_t)~(1u << (uVar11 & 7));
                unsigned local_34 = uVar10;
                int iVar8b = FUN_00065584();
                unsigned uu11 = ((unsigned)uVar1 << 0x1b) >> 0x1d;
                unsigned uu7 = (unsigned)(*(volatile int*)(iVar8b + (local_34 + 0x80) * 4) << 0xe) >> 0x1e;
                if ((int)(((unsigned)(uVar1 >> 2)) << 0x1d) < 0) {
                    FUN_000654c4();
                    local_34 = uVar10;
                    iVar8b = FUN_00065584();
                    if (uu7 == ((unsigned)(*(volatile int*)(iVar8b + (local_34 + 0x80) * 4) << 0xe) >> 0x1e)) {
                        FUN_000851ca();
                        FUN_000851ca();
                    }
                } else {
                    int doC4 = 0;
                    if (uu7 == 2) {
                        FUN_000851ca();
                        if ((uu11 & 5) == 1) doC4 = 1; else goto L_c6a;
                    } else {
                        FUN_000851ca();
                        if (uu11 == 3) doC4 = 1;
                        else if (uu7 == 3) { if (uu11 == 2) doC4 = 1; else goto L_c6a; }
                        else goto L_c6a;
                    }
                    if (doC4) FUN_000654c4();
                }
            L_c6a:
                local_34 = uVar10;
                iVar8b = FUN_00065584();
                *(volatile int*)(iVar8b + 0x20) =
                    (local_34 & 0xff) < 32 ? (int)(1u << (local_34 & 0xff)) : 0;
            }
            piVar12 = piVar12 + 1;
            if (iVar13 != 0) break;
            iVar13 = 1;
        }
        /* LAB_00065cc8 */
        FUN_00065620();
        local_30[0] = *(volatile int*)0x50842520; *(volatile int*)0x50842520 = local_30[0];
        local_30[1] = *(volatile int*)0x50842820; *(volatile int*)0x50842820 = local_30[1];
        if (!(local_30[0] == 0 && local_30[1] == 0)) goto LAB_bce;
        uVar6 = uVar6 & 0x7fffffff;
    }

    while (uVar6 != 0) {
        int iVar9 = __builtin_ctz((unsigned)uVar6);
        FUN_000654c4();
        uVar6 = uVar6 & ~(1 << iVar9);
    }
}

