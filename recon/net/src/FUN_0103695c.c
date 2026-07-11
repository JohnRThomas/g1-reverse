/* net-core FUN_0103695c @ 0x103695c
 * Complete 424-byte worker-loop body through 0x1036b03; its five literals
 * occupy 0x1036b04..0x1036b17 and the next function starts at 0x1036b18.
 * Includes empty-queue waiting, callback dispatch, cancellation-list removal,
 * lock release/reacquisition, and scheduler wakeup. CFG parity: PASS. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern int FUN_01036144(int);
extern int FUN_01036824(int);
extern int FUN_01037a60(void);
extern int FUN_01037e10(int,int,int);
extern int FUN_01037ea8(int,int,int,int,int,int,int);
extern void FUN_01039bb0(int,int);
extern void FUN_01039bbe(int,int,int);
extern int FUN_0103b244(int,int);

typedef int (*fpv_t)(unsigned int);

void FUN_0103695c(int param_1)
{
    unsigned int uVar4 = 0x21004b58u;   /* DAT_01036b04, call-arg only, value irrelevant */
    unsigned int puVar2 = 0x21004b50u;  /* DAT_01036b08, real struct base */

    for (;;) {
        uint32_t saved_basepri = __get_BASEPRI();
        __set_BASEPRI_MAX(0x40);
        __ISB();
        {
            int r = FUN_0103610c((int)uVar4);
            if (r == 0) goto ASSERT_A;
        }
    L_CONT:
        FUN_01036144((int)uVar4);
        {
            unsigned int puVar9 = *(volatile unsigned int*)(param_1 + 0x98);
            if (puVar9 == 0) {
                int iVar3 = FUN_0103b244(param_1 + 0xb0, 2);
                if (iVar3 != 0) {
                    do {
                        iVar3 = FUN_01037e10(param_1 + 0xa8, 1, 0);
                    } while (iVar3 != 0);
                }
                FUN_01037ea8((int)uVar4, (int)saved_basepri,
                             param_1 + 0xa0, -1, -1, -1, 0);
                continue;
            }
            unsigned int uVar7 = *(volatile unsigned int*)puVar9;
            if (puVar9 == *(volatile unsigned int*)(param_1 + 0x9c)) {
                *(volatile unsigned int*)(param_1 + 0x9c) = uVar7;
            }
            *(volatile unsigned int*)(param_1 + 0x98) = uVar7;
            *(volatile unsigned int*)(param_1 + 0xb0) |= 2u;
            unsigned int pcVar12 = *(volatile unsigned int*)(puVar9 + 4);
            *(volatile unsigned int*)(puVar9 + 0xc) =
                (*(volatile unsigned int*)(puVar9 + 0xc) & 0xfffffffbu) | 1u;
            {
                int r2 = FUN_01036128((int)uVar4);
                if (r2 == 0) goto ASSERT_B;
            }
            __set_BASEPRI(saved_basepri);
            __ISB();
            if (pcVar12 == 0) goto ASSERT_C;
            ((fpv_t)(unsigned long)pcVar12)(puVar9);
            uint32_t callback_basepri = __get_BASEPRI();
            __set_BASEPRI_MAX(0x40);
            __ISB();
            {
                int r3 = FUN_0103610c((int)uVar4);
                if (r3 == 0) goto ASSERT_A;
            }
            FUN_01036144((int)uVar4);
            unsigned int uVar8 = *(volatile unsigned int*)(puVar9 + 0xc);
            if ((int)(uVar8 << 0x1e) < 0) {
                unsigned int puVar5 = *(volatile unsigned int*)(unsigned long)puVar2;
                *(volatile unsigned int*)(puVar9 + 0xc) = uVar8 & 0xfffffffcu;
                if (puVar5 != 0) {
                    unsigned int puVar11 = 0;
                    unsigned int puVar13 = *(volatile unsigned int*)(unsigned long)puVar5;
                    while (puVar5 != 0) {
                        unsigned int puVar6 = puVar5;
                        if (puVar9 == *(volatile unsigned int*)(unsigned long)(puVar5 + 4)) {
                            unsigned int uVar7b = *(volatile unsigned int*)(unsigned long)puVar5;
                            if (puVar11 == 0) {
                                *(volatile unsigned int*)(unsigned long)puVar2 = uVar7b;
                                if (*(volatile unsigned int*)(unsigned long)(puVar2 + 4) == puVar5) {
                                    *(volatile unsigned int*)(unsigned long)(puVar2 + 4) = uVar7b;
                                }
                            } else {
                                *(volatile unsigned int*)(unsigned long)puVar11 = uVar7b;
                                if (*(volatile unsigned int*)(unsigned long)(puVar2 + 4) == puVar5) {
                                    *(volatile unsigned int*)(unsigned long)(puVar2 + 4) = puVar11;
                                }
                            }
                            *(volatile unsigned int*)(unsigned long)puVar5 = 0;
                            FUN_01036824((int)(puVar5 + 8));
                            puVar6 = puVar11;
                        }
                        puVar5 = puVar13;
                        puVar11 = puVar6;
                        if (puVar13 != 0) {
                            puVar13 = *(volatile unsigned int*)(unsigned long)puVar13;
                        }
                    }
                }
            } else {
                *(volatile unsigned int*)(puVar9 + 0xc) = uVar8 & 0xfffffffeu;
            }
            unsigned int uVar8b = (*(volatile unsigned int*)(param_1 + 0xb0)) & 0xfffffffdu;
            *(volatile unsigned int*)(param_1 + 0xb0) = uVar8b;
            {
                int r4 = FUN_01036128((int)uVar4);
                if (r4 == 0) goto ASSERT_B;
            }
            __set_BASEPRI(callback_basepri);
            __ISB();
            if ((int)(uVar8b << 0x17) >= 0) {
                FUN_01037a60();
            }
            continue;
        }

    ASSERT_A:
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
        goto L_CONT;
    ASSERT_B:
        FUN_01039bbe(0x0103d2a7, 0x0103d3b6, 0xf0);
        FUN_01039bb0(0x0103d3b6, 0xf0);
        goto L_CONT;
    ASSERT_C:
        FUN_01039bbe(0x0103d2a7, 0x0103eaed, 0x29b);
        FUN_01039bb0(0x0103eaed, 0x29b);
        goto L_CONT;
    }
}
