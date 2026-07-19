#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00014b60 @ 0x00014b60
 * public-name: dtoa_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dcmp_negate_rhs                          <= FUN_0000d588 @ 0x0000d588
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 *   __floatunsidf                            <= FUN_0000d804 @ 0x0000d804
 *   __floatsidf                              <= FUN_0000d824 @ 0x0000d824
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __divdf3                                 <= FUN_0000db4c @ 0x0000db4c
 *   __aeabi_dcmpeq                           <= FUN_0000ddc8 @ 0x0000ddc8
 *   __aeabi_dcmplt                           <= FUN_0000dddc @ 0x0000dddc
 *   __aeabi_dcmpge                           <= FUN_0000de04 @ 0x0000de04
 *   __aeabi_dcmpgt                           <= FUN_0000de18 @ 0x0000de18
 *   __fixdfsi                                <= FUN_0000de58 @ 0x0000de58
 *   dtoa_r                                   <= FUN_00014b60 @ 0x00014b60
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   Balloc                                   <= FUN_000785d4 @ 0x000785d4
 *   Bfree                                    <= FUN_00078654 @ 0x00078654
 *   multadd                                  <= FUN_00078698 @ 0x00078698
 *   i2b                                      <= FUN_000787bc @ 0x000787bc
 *   bigint_mult                              <= FUN_000787e8 @ 0x000787e8
 *   pow5mult                                 <= FUN_0007893c @ 0x0007893c
 *   lshift                                   <= FUN_000789f0 @ 0x000789f0
 *   bigint_diff                              <= FUN_00078ac8 @ 0x00078ac8
 *   d2b_decompose                            <= FUN_00078ce0 @ 0x00078ce0
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   bignum_div_trial_subtract                <= FUN_00087184 @ 0x00087184
 *   clz32                                    <= FUN_00087510 @ 0x00087510
 *   bignum_compare_abs                       <= FUN_000875ae @ 0x000875ae
 * address symbols (name @ address):
 *   rodata_888e0                             @ 0x000888e0
 *   rodata_88908                             @ 0x00088908
 *   rodata_f7a30                             @ 0x000f7a30
 *   rodata_f7a31                             @ 0x000f7a31
 *   rodata_f8baa                             @ 0x000f8baa
 *   rodata_f8bb3                             @ 0x000f8bb3
 *   rodata_f8bb7                             @ 0x000f8bb7
 *   rodata_f8bce                             @ 0x000f8bce
 *   rodata_f8c42                             @ 0x000f8c42
 */
/* Reconstructed FUN_00014b60 @ 0x14b60  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int u32;
typedef unsigned long long u64;

#define LO(x) ((u32)(x))
#define HI(x) ((u32)((u64)(x)>>32))
#define CC(hi,lo) (((u64)(u32)(hi)<<32)|(u32)(lo))
#define P32(a) (*(volatile u32*)(uintptr_t)(u32)(a))
#define P64(a) (*(volatile u64*)(uintptr_t)(u32)(a))
#define PC8(a) (*(volatile char*)(uintptr_t)(u32)(a))

extern u64 dcmp_negate_rhs();
extern u64 __aeabi_dadd();
extern u64 __floatunsidf();
extern u64 __floatsidf();
extern u64 __muldf3();
extern u64 __divdf3();
extern u64 __aeabi_dcmpeq();
extern u64 __aeabi_dcmplt();
extern u64 __aeabi_dcmpge();
extern u64 __aeabi_dcmpgt();
extern u64 __fixdfsi();
extern u64 __assert_func();
extern u64 malloc();
extern u64 Balloc();
extern u64 Bfree();
extern u64 multadd();
extern u64 i2b();
extern u64 bigint_mult();
extern u64 pow5mult();
extern u64 lshift();
extern u64 bigint_diff();
extern u64 d2b_decompose();
extern u64 memcpy();
extern u64 bignum_div_trial_subtract();
extern u64 clz32();
extern u64 bignum_compare_abs();

char *dtoa_r(int a1, u32 a2, int a3, int a4, int a5, int a6, double dval)
{
    u32 param_1 = (u32)a1;
    u32 param_2 = a2;
    u32 param_3 = (u32)a3;
    u32 param_4 = (u32)a4;   /* out decpt   */
    u32 param_5 = (u32)a5;   /* out sign, later reused numerically */
    u32 param_6 = (u32)a6;   /* out rve     */

    u64 in_d0;
    __builtin_memcpy(&in_d0, &dval, 8);

    int bVar1, bVar26, bVar27, bVar28;
    u32 uVar2, uVar5, uVar12, uVar16;
    int iVar6, iVar7, iVar10, iVar13;
    u32 uVar8, uVar9, uVar11;
    u32 pcVar3, pcVar14, pcVar17, pcVar18, pcVar20, pcVar21, pcVar24, pcVar25;
    u32 puVar4, puVar15, puVar19, puVar22;
    u32 local_40, local_50, local_5c, local_74, local_78;
    int local_64, local_68, local_30, local_2c0;
    int kexp;
    int cVar23;
    u64 local_48, local_70, local_80, uVar29, uVar30, uVar31, uVar32;

    pcVar20 = HI(in_d0);
    pcVar14 = LO(in_d0);
    local_80 = in_d0;
    u32 local_60 = param_2;
    local_50 = param_3;

    if (P32(param_1 + 0x24) != 0) goto LAB_b9c;
    pcVar3 = (u32)malloc(0x10);
    P32(param_1 + 0x24) = pcVar3;
    puVar15 = 0;
    param_3 = pcVar3;
    if (pcVar3 != 0) goto LAB_b94;
    uVar9 = 0xea;
    uVar8 = ((unsigned long)&rodata_f8bb7) /*=0xf8bb7*/;
    local_80 = in_d0;
LAB_b8e:
    pcVar3 = (u32)__assert_func(((unsigned long)&rodata_f8bce) /*=0xf8bce*/, uVar9, param_3, uVar8);
LAB_b94:
    P32(pcVar3 + 4) = puVar15;
    P32(pcVar3 + 8) = puVar15;
    P32(pcVar3) = puVar15;
    P32(pcVar3 + 0xc) = puVar15;
LAB_b9c:
    iVar10 = (int)P32(P32(param_1 + 0x24));
    if (iVar10 != 0) {
        uVar12 = P32(P32(param_1 + 0x24) + 4);
        P32(iVar10 + 4) = uVar12;
        P32(iVar10 + 8) = ((uVar12 & 0xff) < 32) ? (1u << (uVar12 & 0xff)) : 0u;
        Bfree(param_1);
        param_3 = 0;
        P32(P32(param_1 + 0x24)) = 0;
    }
    if ((int)pcVar20 < 0) {
        param_3 = 1;
        local_80 = CC(pcVar20, LO(local_80)) & 0x7fffffffffffffffULL;
    } else {
        P32(param_5) = 0;
    }
    uVar32 = local_80;
    uVar12 = 0x7ff00000;
    uVar2 = HI(local_80);
    if ((int)pcVar20 < 0) {
        P32(param_5) = param_3;
    }
    if ((uVar12 & ~HI(local_80)) == 0) {
        P32(param_4) = 9999;
        if ((local_80 & 0xfffff00000000ULL) == 0 && pcVar14 == 0) {
            if (param_6 == 0) return (char *)(uintptr_t)((unsigned long)&rodata_f8baa) /*=0xf8baa*/;
            local_74 = ((unsigned long)&rodata_f8baa) /*=0xf8baa*/;
            pcVar14 = ((unsigned long)&rodata_f8baa) /*=0xf8baa*/ + 8;
        } else {
            if (param_6 == 0) return (char *)(uintptr_t)((unsigned long)&rodata_f8bb3) /*=0xf8bb3*/;
            local_74 = ((unsigned long)&rodata_f8bb3) /*=0xf8bb3*/;
            pcVar14 = ((unsigned long)&rodata_f8bb3) /*=0xf8bb3*/ + 3;
        }
        P32(param_6) = pcVar14;
        return (char *)(uintptr_t)local_74;
    }
    iVar7 = (int)LO(local_80);
    iVar10 = (int)__aeabi_dcmpeq(iVar7, HI(local_80), 0, 0);
    if (iVar10 != 0) {
        P32(param_4) = 1;
        if (param_6 == 0) return (char *)(uintptr_t)((unsigned long)&rodata_f7a30) /*=0xf7a30*/;
        P32(param_6) = ((unsigned long)&rodata_f7a31) /*=0xf7a31*/;
        return (char *)(uintptr_t)((unsigned long)&rodata_f7a30) /*=0xf7a30*/;
    }
    uVar12 = (HI(local_80) << 1) >> 0x15;
    local_78 = (u32)d2b_decompose(iVar7, param_1, (u32)(uintptr_t)&local_2c0, (u32)(uintptr_t)&local_30);
    if (uVar12 == 0) {
        iVar10 = local_30 + local_2c0;
        {
            int t = iVar10 + 0x432;
            bVar26 = (t == 0x20);
            if (t > 0x20) {
                u32 sh1 = (u32)(0x40 - t) & 0x1f;
                u32 sh2 = (u32)(iVar10 + 0x412) & 0x1f;
                uVar5 = (HI(local_80) << sh1) | (pcVar14 >> sh2);
            } else {
                u32 sh = (u32)(0x20 - t) & 0x1f;
                uVar5 = pcVar14 << sh;
            }
        }
        kexp = iVar10 - 1;
        uVar29 = __floatunsidf(uVar5);
        iVar10 = (int)LO(uVar29);
        uVar12 = HI(uVar29) + 0xfe100000;
        bVar27 = 1;
    } else {
        kexp = (int)(uVar12 - 0x3ff);
        uVar12 = (HI(local_80) & 0xfffff) | 0x3ff00000;
        bVar27 = 0;
        iVar10 = iVar7;
    }
    uVar29 = dcmp_negate_rhs(iVar10, uVar12, 0, 0x3ff80000);
    uVar29 = __muldf3(LO(uVar29), HI(uVar29), 0x636f4361, 0x3fd287a7);
    uVar29 = __aeabi_dadd(LO(uVar29), HI(uVar29), 0x8b60c8b3, 0x3fc68a28);
    uVar30 = __floatsidf(kexp);
    uVar30 = __muldf3(LO(uVar30), HI(uVar30), 0x509f79fb, 0x3fd34413);
    uVar29 = __aeabi_dadd(LO(uVar29), HI(uVar29), LO(uVar30), HI(uVar30));
    uVar9 = HI(uVar29);
    puVar4 = (u32)__fixdfsi();
    iVar10 = (int)__aeabi_dcmplt(LO(uVar29), uVar9, 0, 0);
    if (iVar10 != 0) {
        uVar30 = __floatsidf(puVar4);
        iVar10 = (int)__aeabi_dcmpeq(LO(uVar30), HI(uVar30), LO(uVar29), uVar9);
        if (iVar10 == 0) puVar4 = puVar4 - 1;
    }
    if (puVar4 < 0x17) {
        puVar15 = ((unsigned long)&rodata_88908) /*=0x88908*/ + puVar4 * 8;
        iVar10 = (int)__aeabi_dcmplt(iVar7, HI(local_80), P32(puVar15), P32(puVar15 + 4));
        if (iVar10 == 0) { bVar26 = 0; }
        else { puVar4 = puVar4 - 1; bVar26 = 0; }
    } else {
        bVar26 = 1;
    }
    local_64 = (local_30 - kexp) - 1;
    if (local_64 < 0) { local_68 = 1 - (local_30 - kexp); local_64 = 0; }
    else { local_68 = 0; }
    if ((int)puVar4 < 0) {
        local_68 = local_68 - (int)puVar4;
        local_5c = (u32)(-(int)puVar4);
        local_40 = 0;
    } else {
        local_64 = local_64 + (int)puVar4;
        local_5c = 0;
        local_40 = puVar4;
    }
    if (9 < local_60) {
        pcVar14 = 1;
        local_60 = 0;
    Ldefault:
        bVar28 = 1;
        pcVar17 = 0xffffffff;
        local_50 = 0;
        pcVar3 = 0xffffffff;
        pcVar18 = 0x12;
        goto LAB_dc8;
    }
    bVar28 = (5 < (int)local_60);
    if (bVar28) local_60 = local_60 - 4;
    pcVar14 = (u32)(!bVar28);
    switch (local_60) {
    case 2: bVar28 = 0; break;
    case 3: bVar28 = 0; goto LAB_db4;
    case 4: bVar28 = 1; break;
    case 5: bVar28 = 1;
    LAB_db4:
        pcVar3 = puVar4 + local_50;
        pcVar17 = pcVar3 + 1;
        pcVar18 = pcVar17;
        if ((int)pcVar17 < 1) pcVar18 = 1;
        goto LAB_dc8;
    default: goto Ldefault;
    }
    pcVar18 = local_50; pcVar17 = local_50; pcVar3 = local_50;
    if ((int)local_50 < 1) { pcVar18 = 1; pcVar17 = 1; local_50 = 1; pcVar3 = 1; }
LAB_dc8:
    iVar10 = 0;
    for (iVar13 = 4; (pcVar20 = (u32)(iVar13 + 0x14)), pcVar20 <= pcVar18; iVar13 = iVar13 << 1)
        iVar10 = iVar10 + 1;
    P32(P32(param_1 + 0x24) + 4) = iVar10;
    pcVar18 = (u32)Balloc(param_1);
    if (pcVar18 == 0) {
        uVar9 = 0x1aa;
        param_3 = 0;
        uVar8 = ((unsigned long)&rodata_f8c42) /*=0xf8c42*/;
        puVar15 = puVar4;
        local_80 = uVar32;
        goto LAB_b8e;
    }
    P32(P32(param_1 + 0x24)) = pcVar18;
    puVar15 = ((unsigned long)&rodata_888e0) /*=0x888e0*/;
    pcVar20 = local_5c;
    puVar22 = puVar4;
    iVar10 = local_68;
    pcVar21 = pcVar18;
    if ((pcVar17 < 0xf) && (pcVar14 != 0)) {
        if ((int)puVar4 < 1) {
            if (puVar4 == 0) {
                iVar13 = 2;
            } else {
                iVar13 = 2;
                iVar6 = -(int)puVar4 >> 4;
                puVar19 = ((unsigned long)&rodata_88908) /*=0x88908*/ + (-(int)puVar4 & 0xf) * 8;
                local_80 = __muldf3(iVar7, HI(local_80), P32(puVar19), P32(puVar19 + 4));
                bVar1 = 0;
                uVar31 = local_80;
                while (1) {
                    if (iVar6 == 0) break;
                    if (iVar6 << 0x1f < 0) {
                        iVar13 = iVar13 + 1;
                        uVar31 = __muldf3(LO(uVar31), HI(uVar31), P32(puVar15), P32(puVar15 + 4));
                        bVar1 = 1;
                    }
                    iVar6 = iVar6 >> 1;
                    puVar15 = puVar15 + 8;
                }
                if (bVar1) goto LAB_eb8;
            }
        } else {
            uVar12 = (int)puVar4 >> 4;
            local_48 = P64(((unsigned long)&rodata_88908) /*=0x88908*/ + (puVar4 & 0xf) * 8);
            if ((int)(puVar4 << 0x17) < 0) {
                uVar12 = uVar12 & 0xf;
                iVar13 = 3;
                local_80 = __divdf3(iVar7, HI(local_80), P32(((unsigned long)&rodata_888e0) /*=0x888e0*/ + 0x20), P32(((unsigned long)&rodata_888e0) /*=0x888e0*/ + 0x24));
                puVar15 = ((unsigned long)&rodata_888e0) /*=0x888e0*/;
            } else {
                iVar13 = 2;
            }
            while (1) {
                if (uVar12 == 0) break;
                if ((int)(uVar12 << 0x1f) < 0) {
                    iVar13 = iVar13 + 1;
                    local_48 = __muldf3(LO(local_48), HI(local_48), P32(puVar15), P32(puVar15 + 4));
                }
                uVar12 = (int)uVar12 >> 1;
                puVar15 = puVar15 + 8;
            }
            uVar31 = __divdf3(LO(local_80), HI(local_80), LO(local_48), HI(local_48));
        LAB_eb8:
            local_80 = uVar31;
        }
        pcVar14 = pcVar17;
        if (bVar26 &&
            ((iVar6 = (int)__aeabi_dcmplt(LO(local_80), HI(local_80), 0, 0x3ff00000)), iVar6 != 0) &&
            (pcVar17 != 0)) {
            if ((int)pcVar3 < 1) goto LAB_f4c;
            local_80 = __muldf3(LO(local_80), HI(local_80), 0, 0x40240000);
            iVar13 = iVar13 + 1;
            pcVar14 = pcVar3;
            puVar22 = puVar4 - 1;
        }
        uVar29 = __floatsidf(iVar13);
        uVar29 = __muldf3(LO(uVar29), HI(uVar29), LO(local_80), HI(local_80));
        uVar29 = __aeabi_dadd(LO(uVar29), HI(uVar29), 0, 0x401c0000);
        iVar13 = HI(uVar29);
        uVar9 = LO(uVar29);
        iVar6 = iVar13 - 0x3400000;
        if (pcVar14 == 0) {
            uVar29 = dcmp_negate_rhs(LO(local_80), HI(local_80), 0, 0x40140000);
            uVar8 = HI(uVar29);
            iVar6 = (int)__aeabi_dcmpgt(LO(uVar29), uVar8, uVar9, iVar6);
            if (iVar6 == 0) {
                iVar13 = (int)__aeabi_dcmplt(LO(uVar29), uVar8, uVar9, iVar13 + 0x7cc00000);
                if (iVar13 == 0) goto LAB_f4c;
                goto LAB_15180;
            }
        } else {
            iVar13 = ((unsigned long)&rodata_88908) /*=0x88908*/ + (int)pcVar14 * 8;
            uVar8 = P32(iVar13 - 8);
            uVar11 = P32(iVar13 - 4);
            pcVar14 = pcVar14 + pcVar18;
            if (bVar28) {
                uVar29 = __divdf3(0, 0x3fe00000, uVar8, uVar11);
                uVar29 = dcmp_negate_rhs(LO(uVar29), HI(uVar29), uVar9, iVar6);
                pcVar24 = pcVar18;
                while (1) {
                    local_48 = uVar29;
                    cVar23 = (int)__fixdfsi(LO(local_80), HI(local_80));
                    uVar29 = __floatsidf();
                    uVar29 = dcmp_negate_rhs(LO(local_80), HI(local_80), LO(uVar29), HI(uVar29));
                    uVar8 = HI(uVar29);
                    uVar9 = LO(uVar29);
                    pcVar25 = pcVar24 + 1;
                    PC8(pcVar24) = (char)(cVar23 + '0');
                    iVar13 = (int)__aeabi_dcmpgt(LO(local_48), HI(local_48), uVar9, uVar8);
                    if (iVar13 != 0) goto LAB_153a0;
                    uVar29 = dcmp_negate_rhs(0, 0x3ff00000, uVar9, uVar8);
                    iVar13 = (int)__aeabi_dcmpgt(LO(local_48), HI(local_48), LO(uVar29), HI(uVar29));
                    pcVar24 = pcVar25;
                    if (iVar13 != 0) goto LAB_1545e;
                    if (pcVar25 == pcVar14) break;
                    uVar29 = __muldf3(LO(local_48), HI(local_48), 0, 0x40240000);
                    local_80 = __muldf3(uVar9, uVar8, 0, 0x40240000);
                }
                if ((local_2c0 < 0) || (0xe < (int)puVar4)) goto LAB_1542e;
                goto LAB_153dc;
            }
            uVar29 = __muldf3(uVar8, uVar11, uVar9, iVar6);
            uVar9 = HI(uVar29);
            pcVar25 = pcVar18;
            while (1) {
                cVar23 = (int)__fixdfsi(LO(local_80), HI(local_80));
                uVar30 = __floatsidf();
                uVar30 = dcmp_negate_rhs(LO(local_80), HI(local_80), LO(uVar30), HI(uVar30));
                uVar11 = HI(uVar30);
                uVar8 = LO(uVar30);
                pcVar24 = pcVar25 + 1;
                PC8(pcVar25) = (char)(cVar23 + '0');
                if (pcVar24 == pcVar14) break;
                local_80 = __muldf3(uVar8, uVar11, 0, 0x40240000);
                pcVar25 = pcVar24;
            }
            uVar30 = __aeabi_dadd(LO(uVar29), uVar9, 0, 0x3fe00000);
            iVar13 = (int)__aeabi_dcmpgt(uVar8, uVar11, LO(uVar30), HI(uVar30));
            if (iVar13 != 0) goto LAB_1545e;
            uVar29 = dcmp_negate_rhs(0, 0x3fe00000, LO(uVar29), uVar9);
            iVar13 = (int)__aeabi_dcmplt(uVar8, uVar11, LO(uVar29), HI(uVar29));
            if (iVar13 != 0) goto LAB_152e2;
            if ((local_2c0 < 0) || (0xe < (int)puVar4)) goto LAB_f60;
            local_70 = P64(((unsigned long)&rodata_88908) /*=0x88908*/ + (int)puVar4 * 8);
            if ((-1 < (int)local_50) || (pcVar17 != 0)) goto LAB_15338;
        LAB_153fa:
            uVar29 = __muldf3(LO(local_70), HI(local_70), 0, 0x40140000);
            iVar10 = (int)__aeabi_dcmpge(LO(uVar29), HI(uVar29), iVar7, uVar2);
            puVar22 = puVar4;
            if (iVar10 != 0) goto LAB_15180;
        }
        puVar4 = puVar22;
        pcVar14 = 0;
        pcVar21 = pcVar14;
    LAB_15586:
        puVar4 = puVar4 + 1;
        PC8(pcVar18) = '1';
        pcVar25 = pcVar18 + 1;
        goto LAB_1518c;
    }
LAB_f4c:
    if ((local_2c0 < 0) || (0xe < (int)puVar4)) {
        if (bVar28) {
        LAB_1542e:
            if ((int)local_60 < 2) {
                if (bVar27) pcVar14 = (u32)(local_2c0 + 0x433);
                else pcVar14 = (u32)(0x36 - local_30);
            } else {
                pcVar21 = pcVar17 - 1;
                pcVar14 = pcVar17;
                if ((int)local_5c < (int)pcVar21) {
                    local_40 = local_40 + ((int)pcVar21 - (int)local_5c);
                    pcVar20 = 0;
                    local_5c = pcVar21;
                } else {
                    pcVar20 = local_5c - pcVar21;
                    if ((int)pcVar17 < 0) {
                        pcVar14 = 0;
                        iVar10 = local_68 - (int)pcVar17;
                    }
                }
            }
            local_68 = local_68 + (int)pcVar14;
            local_64 = local_64 + (int)pcVar14;
            pcVar21 = (u32)i2b(param_1, 1);
        } else {
        LAB_f60:
            pcVar21 = 0;
        }
        if ((iVar10 != 0) && (0 < local_64)) {
            iVar13 = local_64;
            if (iVar10 <= local_64) iVar13 = iVar10;
            local_68 = local_68 - iVar13;
            iVar10 = iVar10 - iVar13;
            local_64 = local_64 - iVar13;
        }
        if (local_5c != 0) {
            if (bVar28 && (pcVar20 != 0)) {
                pcVar21 = (u32)pow5mult(param_1, pcVar21, pcVar20);
                uVar12 = (u32)bigint_mult(param_1, pcVar21, local_78);
                Bfree(param_1, local_78);
                local_5c = local_5c - pcVar20;
                local_78 = uVar12;
                if (local_5c == 0) goto LAB_fd2;
            }
            local_78 = (u32)pow5mult(param_1, local_78, local_5c);
        }
    LAB_fd2:
        pcVar14 = (u32)i2b(param_1, 1);
        if (local_40 == 0) {
            if (((int)local_60 < 2) && (iVar7 == 0)) goto LAB_154f6;
        LAB_15522:
            iVar7 = 1;
        } else {
            pcVar14 = (u32)pow5mult(param_1, pcVar14, local_40);
            if (((int)local_60 < 2) && (iVar7 == 0)) {
            LAB_154f6:
                if ((uVar32 & 0xfffff00000000ULL) == 0) {
                    puVar15 = (uVar2 & 0x7ff00000);
                    if ((uVar32 & 0x7ff0000000000000ULL) != 0) {
                        puVar15 = 1;
                        local_68 = local_68 + 1;
                        local_64 = local_64 + 1;
                    }
                } else {
                    puVar15 = 0;
                }
                bVar27 = (local_40 == 0);
                local_40 = puVar15;
                if (bVar27) goto LAB_15522;
            } else {
                puVar15 = 0;
            }
            iVar7 = (int)clz32(P32(pcVar14 + (P32(pcVar14 + 0x10) + 4) * 4));
            iVar7 = 0x20 - iVar7;
            local_40 = puVar15;
        }
        uVar12 = (local_64 + iVar7) & 0x1f;
        if (uVar12 == 0) {
            iVar7 = 0;
        LAB_1552e:
            iVar7 = iVar7 + 0x1c;
            local_68 = local_68 + iVar7;
            iVar10 = iVar10 + iVar7;
            local_64 = local_64 + iVar7;
        } else {
            iVar7 = 0x20 - uVar12;
            if (iVar7 < 5) {
                if (iVar7 != 4) goto LAB_1552e;
            } else {
                iVar7 = 0x1c - uVar12;
                local_68 = local_68 + iVar7;
                iVar10 = iVar10 + iVar7;
                local_64 = local_64 + iVar7;
            }
        }
        if (0 < local_68) local_78 = (u32)lshift(param_1, local_78, local_68);
        if (0 < local_64) pcVar14 = (u32)lshift(param_1, pcVar14, local_64);
        pcVar20 = pcVar18;
        if (bVar26 && ((iVar7 = (int)bignum_compare_abs(local_78, pcVar14)), iVar7 < 0)) {
            local_78 = (u32)multadd(param_1, local_78, 10, 0);
            puVar4 = puVar4 - 1;
            pcVar17 = pcVar3;
            if (bVar28) {
                pcVar21 = (u32)multadd(param_1, pcVar21, 10, 0);
                if ((0 < (int)pcVar3) || ((int)local_60 < 3)) goto LAB_150a8;
            } else if ((0 < (int)pcVar3) || ((int)local_60 < 3)) goto LAB_155a4;
        } else if ((0 < (int)pcVar17) || ((int)local_60 < 3)) {
            pcVar3 = pcVar17;
            if (!bVar28) goto LAB_155a4;
        LAB_150a8:
            pcVar20 = pcVar21;
            if (0 < iVar10) pcVar20 = (u32)lshift(param_1, pcVar21, iVar10);
            pcVar21 = pcVar20;
            if (local_40 == 0) goto LAB_155ea;
            iVar10 = (int)Balloc(param_1, P32(pcVar20 + 4));
            if (iVar10 == 0) {
                uVar9 = 0x2ea;
                param_3 = 0;
                puVar15 = 0;
                uVar8 = ((unsigned long)&rodata_f8c42) /*=0xf8c42*/;
                param_5 = puVar4;
                local_80 = uVar32;
                goto LAB_b8e;
            }
            memcpy(iVar10 + 0xc, pcVar20 + 0xc, (P32(pcVar20 + 0x10) + 2) * 4);
            pcVar21 = (u32)lshift(param_1, iVar10, 1);
        LAB_155ea:
            pcVar24 = pcVar18;
            while (1) {
                pcVar3 = pcVar24 + 1;
                iVar10 = (int)bignum_div_trial_subtract(local_78, pcVar14);
                uVar12 = iVar10 + 0x30;
                iVar7 = (int)bignum_compare_abs(local_78, pcVar20);
                iVar13 = (int)bigint_diff(param_1, pcVar14, pcVar21);
                if (P32(iVar13 + 0xc) != 0) break;
                iVar6 = (int)bignum_compare_abs(local_78, iVar13);
                Bfree(param_1, iVar13);
                if (iVar6 == 0) {
                    if ((local_60 == 0) && ((uVar32 & 1) == 0)) {
                        if (uVar12 == 0x39) goto LAB_156c8;
                        if (0 < iVar7) goto LAB_1569c;
                        goto LAB_156a8;
                    }
                    if (iVar7 < 0) goto LAB_156a8;
                } else {
                    if ((iVar7 < 0) || ((local_60 == 0 && iVar7 == 0 && ((uVar32 & 1) == 0)))) {
                        if (0 < iVar6) goto LAB_1563c;
                        goto LAB_156a8;
                    }
                    if (0 < iVar6) goto LAB_156c2;
                }
                PC8(pcVar24) = (char)uVar12;
                if (pcVar17 + pcVar18 == pcVar3) goto LAB_15768;
                local_78 = (u32)multadd(param_1, local_78, 10, 0);
                pcVar24 = pcVar3;
                if (pcVar20 == pcVar21) {
                    pcVar21 = (u32)multadd(param_1, pcVar20, 10, 0);
                    pcVar20 = pcVar21;
                } else {
                    pcVar20 = (u32)multadd(param_1, pcVar20, 10, 0);
                    pcVar21 = (u32)multadd(param_1, pcVar21, 10, 0);
                }
            }
            Bfree(param_1);
            if ((iVar7 < 0) || ((local_60 == 0 && iVar7 == 0 && ((uVar32 & 1) == 0)))) {
            LAB_1563c:
                local_78 = (u32)lshift(param_1, local_78, 1);
                iVar7 = (int)bignum_compare_abs(local_78, pcVar14);
                if ((0 < iVar7) || ((iVar7 == 0 && ((uVar12 & 1) != 0)))) {
                    if (uVar12 == 0x39) goto LAB_156c8;
                LAB_1569c:
                    uVar12 = iVar10 + 0x31;
                }
            LAB_156a8:
                cVar23 = (char)uVar12;
            } else {
            LAB_156c2:
                if (uVar12 == 0x39) {
                LAB_156c8:
                    PC8(pcVar24) = '9';
                    pcVar3 = pcVar24 + 1;
                    goto LAB_156d0;
                }
                cVar23 = (char)uVar12 + 1;
            }
            pcVar25 = pcVar24 + 1;
            PC8(pcVar24) = (char)cVar23;
            goto LAB_15190;
        }
        if (pcVar17 == 0) {
            pcVar14 = (u32)multadd(param_1, pcVar14, 5);
            iVar10 = (int)bignum_compare_abs(local_78, pcVar14);
            if (0 < iVar10) goto LAB_15586;
        }
    } else {
    LAB_153dc:
        local_70 = P64(((unsigned long)&rodata_88908) /*=0x88908*/ + (int)puVar4 * 8);
        if ((-1 < (int)local_50) || (0 < (int)pcVar17)) goto LAB_15338;
        if (pcVar17 == 0) goto LAB_153fa;
    LAB_15180:
        pcVar14 = 0;
        pcVar21 = 0;
    }
    puVar4 = ~local_50;
    pcVar25 = pcVar18;
LAB_1518c:
    pcVar20 = 0;
    goto LAB_15190;
LAB_152e2:
    do {
        pcVar25 = pcVar14;
        pcVar14 = pcVar25 - 1;
    } while (PC8(pcVar25 - 1) == '0');
    goto LAB_153a0;
LAB_155a4:
    while (1) {
        iVar10 = (int)bignum_div_trial_subtract(local_78, pcVar14);
        uVar12 = iVar10 + 0x30;
        PC8(pcVar20) = (char)uVar12;
        if ((int)pcVar3 <= (int)((pcVar20 + 1) - pcVar18)) break;
        local_78 = (u32)multadd(param_1, local_78, 10, 0);
        pcVar20 = pcVar20 + 1;
    }
    pcVar20 = 0;
    if ((int)pcVar3 < 1) pcVar3 = 1;
    pcVar3 = pcVar3 + pcVar18;
LAB_15768:
    local_78 = (u32)lshift(param_1, local_78, 1);
    iVar10 = (int)bignum_compare_abs(local_78, pcVar14);
    if ((iVar10 < 1) && ((iVar10 != 0 || ((uVar12 & 1) == 0)))) {
        do {
            pcVar25 = pcVar3;
            pcVar3 = pcVar25 - 1;
        } while (PC8(pcVar25 - 1) == '0');
    } else {
    LAB_156d0:
        do {
            pcVar25 = pcVar3;
            pcVar3 = pcVar25 - 1;
            if (PC8(pcVar25 - 1) != '9') {
                PC8(pcVar3) = (char)(PC8(pcVar25 - 1) + 1);
                goto LAB_15190;
            }
        } while (pcVar18 != pcVar3);
        puVar4 = puVar4 + 1;
        PC8(pcVar18) = '1';
    }
LAB_15190:
    Bfree(param_1, pcVar14);
    puVar22 = puVar4;
    if (pcVar21 != 0) {
        if ((pcVar20 != 0) && (pcVar20 != pcVar21)) Bfree(param_1, pcVar20);
        Bfree(param_1, pcVar21);
    }
    goto LAB_153a0;
    while (1) {
        uVar32 = __muldf3(uVar9, uVar8, 0, 0x40140000);
        iVar10 = (int)__aeabi_dcmpeq(LO(uVar32), HI(uVar32), 0, 0);
        puVar22 = puVar4;
        pcVar21 = pcVar25;
        if (iVar10 != 0) break;
    LAB_15338:
        uVar9 = HI(uVar32);
        __divdf3(LO(uVar32), uVar9, LO(local_70), HI(local_70));
        iVar10 = (int)__fixdfsi();
        uVar29 = __floatsidf();
        uVar29 = __muldf3(LO(uVar29), HI(uVar29), LO(local_70), HI(local_70));
        uVar29 = dcmp_negate_rhs(LO(uVar32), uVar9, LO(uVar29), HI(uVar29));
        uVar8 = HI(uVar29);
        uVar9 = LO(uVar29);
        pcVar25 = pcVar21 + 1;
        PC8(pcVar21) = (char)(iVar10 + '0');
        if (pcVar17 == pcVar25 - pcVar18) {
            uVar29 = __aeabi_dadd(uVar9, uVar8, uVar9, uVar8);
            uVar9 = HI(uVar29);
            iVar7 = (int)__aeabi_dcmpgt(LO(uVar29), uVar9, LO(local_70), HI(local_70));
            pcVar24 = pcVar25;
            puVar22 = puVar4;
            if ((iVar7 != 0) ||
                (((iVar7 = (int)__aeabi_dcmpeq(LO(uVar29), uVar9, LO(local_70), HI(local_70))), iVar7 != 0)
                 && (iVar10 << 0x1f < 0))) goto LAB_1545e;
            break;
        }
    }
    goto LAB_153a0;
LAB_1545e:
    pcVar25 = pcVar24;
    pcVar24 = pcVar25 - 1;
    if (PC8(pcVar24) != '9') goto LAB_15476;
    while (pcVar18 != pcVar24) {
        pcVar25 = pcVar24;
        pcVar24 = pcVar25 - 1;
        if (PC8(pcVar24) != '9') goto LAB_15476;
    }
    puVar22 = puVar22 + 1;
    PC8(pcVar18) = '0';
LAB_15476:
    PC8(pcVar24) = (char)(PC8(pcVar24) + 1);
LAB_153a0:
    Bfree(param_1, local_78);
    PC8(pcVar25) = '\0';
    P32(param_4) = (int)puVar22 + 1;
    if (param_6 != 0) P32(param_6) = pcVar25;
    return (char *)(uintptr_t)pcVar18;
}
