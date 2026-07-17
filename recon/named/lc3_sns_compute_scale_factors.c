/* readable reconstruction; identity: FUN_0006bfc8 @ 0x0006bfc8
 * public-name: lc3_sns_compute_scale_factors
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_sns_compute_scale_factors            <= FUN_0006bfc8 @ 0x0006bfc8
 * address symbols (name @ address):
 *   lc3_band_lim                             @ 0x00090c50
 */
/* Reconstructed FUN_0006bfc8 @ 0x6bfc8  (parity: 300/300 trials, PROVEN void, nptr=3) */
extern void *FUN_00086c44(void *dst, void *src, int n);

#define local_124 buf[5]
#define local_120 buf[6]
#define local_11c buf[7]
#define local_118 buf[8]
#define local_114 buf[9]
#define local_110 buf[10]
#define local_10c buf[11]
#define local_108 buf[12]
#define local_104 buf[13]
#define local_100 buf[14]
#define local_fc buf[15]
#define local_f8 buf[16]
#define local_f4 buf[17]
#define local_f0 buf[18]
#define local_ec buf[19]
#define local_e8 buf[20]
#define local_e4 buf[21]
#define local_e0 buf[22]
#define local_dc buf[23]
#define local_d8 buf[24]
#define local_d4 buf[25]
#define local_d0 buf[26]
#define local_cc buf[27]
#define local_c8 buf[28]
#define local_c4 buf[29]
#define local_c0 buf[30]
#define local_bc buf[31]
#define local_b8 buf[32]
#define local_b4 buf[33]
#define local_b0 buf[34]
#define local_ac buf[35]
#define local_a8 buf[36]
#define local_a4 buf[37]
#define local_a0 buf[38]
#define local_9c buf[39]
#define local_98 buf[40]
#define local_94 buf[41]
#define local_90 buf[42]
#define local_8c buf[43]
#define local_88 buf[44]
#define local_84 buf[45]
#define local_80 buf[46]
#define local_7c buf[47]
#define local_78 buf[48]
#define local_74 buf[49]
#define local_70 buf[50]
#define local_6c buf[51]
#define local_68 buf[52]
#define local_64 buf[53]
#define local_60 buf[54]
#define local_5c buf[55]
#define local_58 buf[56]
#define local_54 buf[57]
#define local_50 buf[58]
#define local_4c buf[59]
#define local_48 buf[60]
#define local_44 buf[61]
#define local_40 buf[62]
#define local_3c buf[63]

void lc3_sns_compute_scale_factors(int param_1, int param_2, float *param_3, int param_4,
                  int param_5, int param_6)
{
    /* The in-place collapse reads pairs through element 127 when the
       configured count is zero, then compacts the upper half downward. */
    float buf[128];
    float *pfVar1;
    float *pfVar3;
    float *pfVar4;
    float *pfVar7;
    int iVar2;
    int iVar5;
    int iVar6;
    int iVar8;
    int *piVar9;
    float fVar10, fVar11, fVar12, fVar13, fVar14, fVar15, fVar16, fVar17;
    float fVar18, fVar19, fVar20, fVar21;

    buf[1] = *param_3;
    if (param_4 == 0) {
        fVar14 = param_3[1];
        fVar19 = fVar14 - buf[1];
        buf[2] = buf[1] + fVar19 * 0.125f;
        fVar15 = param_3[2];
        buf[0] = buf[1];
        buf[3] = buf[1] + fVar19 * 0.375f;
        fVar10 = fVar15 - fVar14;
        local_124 = buf[1] + fVar19 * 0.875f;
        fVar16 = param_3[3];
        local_120 = fVar14 + fVar10 * 0.125f;
        fVar11 = fVar16 - fVar15;
        local_11c = fVar14 + fVar10 * 0.375f;
        fVar17 = param_3[4];
        fVar18 = param_3[5];
        fVar12 = fVar17 - fVar16;
        local_10c = fVar15 + fVar11 * 0.375f;
        local_118 = fVar14 + fVar10 * 0.625f;
        local_110 = fVar15 + fVar11 * 0.125f;
        fVar13 = fVar18 - fVar17;
        local_114 = fVar14 + fVar10 * 0.875f;
        fVar14 = param_3[6];
        fVar10 = fVar14 - fVar18;
        local_ec = fVar17 + fVar13 * 0.375f;
        local_108 = fVar15 + fVar11 * 0.625f;
        local_104 = fVar15 + fVar11 * 0.875f;
        local_100 = fVar16 + fVar12 * 0.125f;
        buf[4] = buf[1] + fVar19 * 0.625f;
        local_fc = fVar16 + fVar12 * 0.375f;
        local_f8 = fVar16 + fVar12 * 0.625f;
        local_f4 = fVar16 + fVar12 * 0.875f;
        local_f0 = fVar17 + fVar13 * 0.125f;
        local_e8 = fVar17 + fVar13 * 0.625f;
        local_e4 = fVar17 + fVar13 * 0.875f;
        local_e0 = fVar18 + fVar10 * 0.125f;
        local_dc = fVar18 + fVar10 * 0.375f;
        local_d8 = fVar18 + fVar10 * 0.625f;
        local_d4 = fVar18 + fVar10 * 0.875f;
        fVar10 = param_3[7];
        fVar19 = fVar10 - fVar14;
        local_d0 = fVar14 + fVar19 * 0.125f;
        fVar12 = param_3[8];
        local_cc = fVar14 + fVar19 * 0.375f;
        fVar11 = fVar12 - fVar10;
        local_c4 = fVar14 + fVar19 * 0.875f;
        local_c0 = fVar10 + fVar11 * 0.125f;
        fVar15 = param_3[9];
        local_bc = fVar10 + fVar11 * 0.375f;
        fVar13 = fVar15 - fVar12;
        local_b4 = fVar10 + fVar11 * 0.875f;
        local_b8 = fVar10 + fVar11 * 0.625f;
        fVar16 = param_3[10];
        local_b0 = fVar12 + fVar13 * 0.125f;
        fVar17 = param_3[0xb];
        fVar10 = fVar16 - fVar15;
        local_ac = fVar12 + fVar13 * 0.375f;
        fVar18 = param_3[0xc];
        fVar11 = fVar17 - fVar16;
        local_a8 = fVar12 + fVar13 * 0.625f;
        local_a4 = fVar12 + fVar13 * 0.875f;
        fVar20 = param_3[0xd];
        fVar12 = fVar18 - fVar17;
        local_9c = fVar15 + fVar10 * 0.375f;
        local_a0 = fVar15 + fVar10 * 0.125f;
        fVar13 = fVar20 - fVar18;
        local_98 = fVar15 + fVar10 * 0.625f;
        local_94 = fVar15 + fVar10 * 0.875f;
        local_90 = fVar16 + fVar11 * 0.125f;
        local_80 = fVar17 + fVar12 * 0.125f;
        local_88 = fVar16 + fVar11 * 0.625f;
        local_84 = fVar16 + fVar11 * 0.875f;
        local_78 = fVar17 + fVar12 * 0.625f;
        local_74 = fVar17 + fVar12 * 0.875f;
        local_70 = fVar18 + fVar13 * 0.125f;
        local_c8 = fVar14 + fVar19 * 0.625f;
        local_7c = fVar17 + fVar12 * 0.375f;
        local_8c = fVar16 + fVar11 * 0.375f;
        local_6c = fVar18 + fVar13 * 0.375f;
        local_4c = param_3[0xe];
        fVar10 = param_3[0xf];
        fVar11 = local_4c - fVar20;
        local_68 = fVar18 + fVar13 * 0.625f;
        local_64 = fVar18 + fVar13 * 0.875f;
        fVar12 = fVar10 - local_4c;
        fVar14 = fVar12 * 0.125f;
        fVar13 = fVar12 * 0.375f;
        local_48 = local_4c + fVar12 * 0.625f;
        local_60 = fVar20 + fVar11 * 0.125f;
        local_44 = local_4c + fVar12 * 0.875f;
        local_5c = fVar20 + fVar11 * 0.375f;
        local_50 = fVar14 + local_4c;
        local_58 = fVar20 + fVar11 * 0.625f;
        local_4c = fVar13 + local_4c;
        local_54 = fVar20 + fVar11 * 0.875f;
    }
    else {
        fVar13 = param_3[1];
        buf[0] = -buf[1];
        fVar18 = buf[1] - fVar13;
        fVar15 = param_3[2];
        buf[1] = buf[0];
        buf[3] = buf[0] + fVar18 * 0.375f;
        fVar11 = fVar13 - fVar15;
        local_124 = buf[0] + fVar18 * 0.875f;
        fVar16 = param_3[3];
        fVar14 = fVar15 - fVar16;
        local_11c = -fVar13 + fVar11 * 0.375f;
        local_120 = -fVar13 + fVar11 * 0.125f;
        fVar12 = param_3[5];
        fVar17 = param_3[4];
        fVar19 = fVar16 - fVar17;
        fVar10 = fVar17 - fVar12;
        local_118 = -fVar13 + fVar11 * 0.625f;
        local_114 = -fVar13 + fVar11 * 0.875f;
        local_110 = -fVar15 + fVar14 * 0.125f;
        fVar13 = param_3[6];
        buf[2] = buf[0] + fVar18 * 0.125f;
        buf[4] = buf[0] + fVar18 * 0.625f;
        fVar11 = fVar12 - fVar13;
        local_10c = -fVar15 + fVar14 * 0.375f;
        local_ec = -fVar17 + fVar10 * 0.375f;
        local_108 = -fVar15 + fVar14 * 0.625f;
        local_104 = -fVar15 + fVar14 * 0.875f;
        local_100 = -fVar16 + fVar19 * 0.125f;
        local_fc = -fVar16 + fVar19 * 0.375f;
        local_f8 = -fVar16 + fVar19 * 0.625f;
        local_f4 = -fVar16 + fVar19 * 0.875f;
        local_f0 = -fVar17 + fVar10 * 0.125f;
        local_e4 = -fVar17 + fVar10 * 0.875f;
        local_e0 = -fVar12 + fVar11 * 0.125f;
        local_dc = -fVar12 + fVar11 * 0.375f;
        local_d8 = -fVar12 + fVar11 * 0.625f;
        local_d4 = -fVar12 + fVar11 * 0.875f;
        local_e8 = -fVar17 + fVar10 * 0.625f;
        fVar14 = param_3[7];
        fVar11 = fVar13 - fVar14;
        local_d0 = -fVar13 + fVar11 * 0.125f;
        fVar15 = param_3[8];
        local_cc = -fVar13 + fVar11 * 0.375f;
        fVar10 = fVar14 - fVar15;
        local_c4 = -fVar13 + fVar11 * 0.875f;
        local_c0 = -fVar14 + fVar10 * 0.125f;
        local_bc = -fVar14 + fVar10 * 0.375f;
        fVar16 = param_3[9];
        fVar12 = fVar15 - fVar16;
        local_b8 = -fVar14 + fVar10 * 0.625f;
        local_b4 = -fVar14 + fVar10 * 0.875f;
        fVar17 = param_3[10];
        fVar21 = fVar16 - fVar17;
        local_ac = -fVar15 + fVar12 * 0.375f;
        local_b0 = -fVar15 + fVar12 * 0.125f;
        fVar18 = param_3[0xb];
        fVar14 = param_3[0xc];
        fVar20 = fVar17 - fVar18;
        fVar19 = fVar18 - fVar14;
        local_a8 = -fVar15 + fVar12 * 0.625f;
        local_a4 = -fVar15 + fVar12 * 0.875f;
        local_a0 = -fVar16 + fVar21 * 0.125f;
        fVar12 = param_3[0xd];
        fVar10 = fVar14 - fVar12;
        local_9c = -fVar16 + fVar21 * 0.375f;
        local_7c = -fVar18 + fVar19 * 0.375f;
        local_98 = -fVar16 + fVar21 * 0.625f;
        local_90 = -fVar17 + fVar20 * 0.125f;
        local_94 = -fVar16 + fVar21 * 0.875f;
        local_84 = -fVar17 + fVar20 * 0.875f;
        local_78 = -fVar18 + fVar19 * 0.625f;
        local_74 = -fVar18 + fVar19 * 0.875f;
        local_70 = -fVar14 + fVar10 * 0.125f;
        local_c8 = -fVar13 + fVar11 * 0.625f;
        local_8c = -fVar17 + fVar20 * 0.375f;
        local_88 = -fVar17 + fVar20 * 0.625f;
        local_80 = -fVar18 + fVar19 * 0.125f;
        local_6c = -fVar14 + fVar10 * 0.375f;
        local_4c = param_3[0xe];
        local_68 = -fVar14 + fVar10 * 0.625f;
        fVar11 = fVar12 - local_4c;
        local_64 = -fVar14 + fVar10 * 0.875f;
        fVar10 = local_4c - param_3[0xf];
        fVar14 = fVar10 * 0.125f;
        fVar13 = fVar10 * 0.375f;
        local_48 = -local_4c + fVar10 * 0.625f;
        local_44 = -local_4c + fVar10 * 0.875f;
        fVar10 = -param_3[0xf];
        local_50 = fVar14 - local_4c;
        local_60 = -fVar12 + fVar11 * 0.125f;
        local_4c = fVar13 - local_4c;
        local_5c = -fVar12 + fVar11 * 0.375f;
        local_58 = -fVar12 + fVar11 * 0.625f;
        local_54 = -fVar12 + fVar11 * 0.875f;
    }
    pfVar7 = buf;
    iVar8 = *(volatile int *)(param_1 * 0x514 + param_2 * 0x104 + 0x00090c50 + 0x100);
    iVar6 = iVar8;
    if (0x3f < iVar8) {
        iVar6 = 0x40;
    }
    iVar2 = 0x40 - iVar6;
    local_40 = fVar14 + fVar10;
    local_3c = fVar10 + fVar13;
    if (iVar2 != 0) {
        pfVar3 = pfVar7;
        pfVar4 = pfVar7;
        buf[0] = buf[1];
        do {
            fVar10 = *pfVar3;
            pfVar1 = pfVar3 + 1;
            pfVar3 = pfVar3 + 2;
            *pfVar4 = (fVar10 + *pfVar1) * 0.5f;
            pfVar4 = pfVar4 + 1;
        } while (pfVar3 != pfVar7 + iVar2 * 2);
        FUN_00086c44(pfVar7 + iVar2, pfVar7 + iVar2 * 2, (iVar6 - iVar2) * 4);
    }
    fVar14 = 0x1.62e42ep-5f;
    fVar13 = 0x1.ebfaacp-11f;
    fVar12 = 0x1.c6b278p-17f;
    fVar11 = 0x1.3c9260p-23f;
    fVar10 = 0x1.5d9ee8p-30f;
    piVar9 = (int *)(0x00090c50 + param_1 * 0x514 + param_2 * 0x104);
    if (0 < iVar8) {
        iVar8 = 0;
        iVar5 = 0;
        do {
            fVar15 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            fVar15 = 1.0f - fVar15 * (fVar14 - fVar15 * (fVar13 - fVar15 *
                     (fVar12 - fVar15 * (fVar11 - fVar15 * fVar10))));
            fVar15 = fVar15 * fVar15;
            fVar15 = fVar15 * fVar15;
            fVar15 = fVar15 * fVar15;
            fVar15 = fVar15 * fVar15;
            piVar9 = piVar9 + 1;
            if (iVar5 < *(volatile int *)piVar9) {
                pfVar3 = (float *)(param_5 + iVar5 * 4);
                pfVar4 = (float *)(param_6 + iVar5 * 4);
                do {
                    fVar16 = *pfVar3;
                    pfVar3 = pfVar3 + 1;
                    *pfVar4 = fVar16 * fVar15;
                    pfVar4 = pfVar4 + 1;
                    iVar5 = iVar5 + 1;
                } while (iVar5 < *(volatile int *)piVar9);
            }
            iVar8 = iVar8 + 1;
        } while (iVar8 < iVar6);
    }
    return;
}
