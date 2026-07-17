#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006ffd8 @ 0x0006ffd8
 * public-name: FUN_0006ffd8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_8853c                             @ 0x0008853c
 *   rodata_98540                             @ 0x00098540
 *   rodata_98564                             @ 0x00098564
 */
/* Reconstructed FUN_0006ffd8 @ 0x6ffd8  (parity: 40/40 trials, PROVEN) */
typedef unsigned int uint;
typedef unsigned char undefined1;

#define DAT_00070398 ((float*)((unsigned long)&rodata_8853c) /*=0x8853c*/)
#define DAT_0007039c (0.0f)
#define DAT_000703a0 (0x1.8p+1f)
#define DAT_000703a4 (0x1.f01514p-1f)
#define DAT_000703a8 (0x1.fbf92cp-1f)
#define DAT_000703ac (0x1.f6fc08p-1f)
#define DAT_000703b0 (0x1.fefd88p-1f)
#define DAT_000703b4 (0x1.e758dcp-1f)
#define DAT_000703b8 (0x1.dce11cp-1f)
#define DAT_000703bc (0x1.d0cc3ep-1f)
#define DAT_000703c0 (0x1.c33ccap-1f)
#define DAT_000709c8 (0x1.7a5f6p-1f)
#define DAT_000709cc (((unsigned long)&rodata_98564) /*=0x98564*/)
#define DAT_000709d0 (0x1.33333p-2f)
#define DAT_000709d4 (((unsigned long)&rodata_98540) /*=0x98540*/)

void FUN_0006ffd8(int param_1,uint param_2,int param_3,int param_4,int *param_5,int param_6)
{
  int bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int *piVar6;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  uint uVar11;
  undefined1 uVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar16;
  uint uVar17;
  int iVar18;
  float *pfVar19;
  int iVar20;
  int iVar21;
  float *pfVar22;
  uint *puVar23;
  int *piVar24;
  float *pfVar25;
  float *pfVar26;
  int *piVar27;
  uint *puVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float local_154 [10];
  float local_12c;
  float local_128;
  float local_124;
  float local_11c [4];
  float local_10c;
  float local_108;
  float fStack_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4 [18];
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float *pfVar15;

  pfVar22 = DAT_00070398;
  if (2 < param_2) {
    iVar20 = 2;
  }
  else {
    iVar20 = 1;
  }
  if (param_1 == 0) {
    iVar8 = 0x2d;
  }
  else {
    iVar8 = 0x3c;
  }
  iVar13 = param_4;
  if (iVar8 <= param_4) {
    iVar13 = 0;
  }
  uVar12 = (undefined1)iVar13;
  if (param_4 < iVar8) {
    uVar12 = 1;
  }
  *(undefined1 *)(param_5 + 1) = uVar12;
  *param_5 = iVar20;
  local_11c[0] = *pfVar22;
  local_11c[1] = pfVar22[1];
  local_11c[2] = pfVar22[2];
  local_11c[3] = pfVar22[3];
  local_10c = pfVar22[4];
  local_108 = pfVar22[5];
  fStack_104 = pfVar22[6];
  local_100 = pfVar22[7];
  pfVar16 = local_e4;
  local_fc = pfVar22[8];
  local_f8 = pfVar22[9];
  piVar6 = (int *)(int)local_11c[param_1 * 5 + param_2];
  piVar24 = piVar6 + iVar20 * 3;
  pfVar9 = (float *)(param_6 + *piVar6 * 4);
  pfVar22 = pfVar16;
  do {
    pfVar7 = &local_9c;
    piVar27 = piVar6 + 3;
    pfVar10 = pfVar9;
    do {
      piVar6 = piVar6 + 1;
      pfVar9 = (float *)(param_6 + *piVar6 * 4);
      iVar13 = (int)pfVar9 - (int)pfVar10 >> 2;
      pfVar19 = pfVar9;
      iVar8 = iVar13;
      pfVar25 = pfVar7;
      do {
        iVar21 = iVar8 + -1;
        pfVar26 = (float *)(((int)pfVar10 + iVar13 * 2) * 2 - (int)pfVar19);
        pfVar14 = pfVar10;
        fVar45 = DAT_0007039c;
        if (iVar8 != 0) {
          do {
            pfVar15 = pfVar14 + 1;
            fVar39 = *pfVar26;
            pfVar26 = pfVar26 + 1;
            fVar45 = fVar45 + *pfVar14 * fVar39;
            pfVar14 = pfVar15;
          } while (pfVar15 != pfVar19);
        }
        *pfVar25 = fVar45;
        fVar31 = local_94;
        fVar39 = local_98;
        fVar45 = local_9c;
        pfVar25 = pfVar25 + 3;
        pfVar19 = pfVar19 + -1;
        iVar8 = iVar21;
      } while (iVar13 + -9 != iVar21);
      pfVar7 = pfVar7 + 1;
      pfVar10 = pfVar9;
    } while (piVar6 != piVar27);
    bVar1 = local_9c == 0.0;
    *pfVar22 = DAT_000703a0;
    if (((bVar1) || (fVar39 == 0.0)) || (fVar31 == 0.0)) {
      pfVar22[1] = DAT_0007039c;
      pfVar22[2] = DAT_0007039c;
      pfVar22[3] = DAT_0007039c;
      pfVar22[4] = DAT_0007039c;
      pfVar22[5] = DAT_0007039c;
      pfVar22[6] = DAT_0007039c;
      pfVar22[7] = DAT_0007039c;
      fVar45 = DAT_0007039c;
    }
    else {
      fVar39 = 1.0 / fVar39;
      fVar45 = 1.0 / fVar45;
      fVar31 = 1.0 / fVar31;
      fVar37 = fVar39 * local_50;
      fVar41 = fVar39 * local_8c;
      fVar33 = fVar39 * local_74;
      fVar34 = fVar39 * local_68;
      fVar36 = fVar39 * local_5c;
      fVar38 = fVar39 * local_44;
      fVar47 = fVar39 * local_38;
      fVar46 = local_78 * fVar45;
      fVar29 = local_6c * fVar45;
      fVar30 = local_60 * fVar45;
      fVar35 = local_54 * fVar45;
      fVar40 = local_48 * fVar45;
      fVar48 = local_3c * fVar45;
      fVar42 = local_90 * fVar45;
      fVar32 = local_70 * fVar31;
      fVar43 = local_64 * fVar31;
      fVar44 = local_58 * fVar31;
      fVar2 = local_88 * fVar31;
      fVar3 = local_4c * fVar31;
      fVar4 = local_40 * fVar31;
      fVar5 = local_34 * fVar31;
      pfVar22[2] = (fVar39 * local_80 + local_84 * fVar45 + local_7c * fVar31) * DAT_000703a8;
      pfVar22[3] = (fVar33 + fVar46 + fVar32) * DAT_000703ac;
      pfVar22[4] = (fVar34 + fVar29 + fVar43) * DAT_000703a4;
      pfVar22[1] = (fVar41 + fVar42 + fVar2) * DAT_000703b0;
      pfVar22[5] = (fVar36 + fVar30 + fVar44) * DAT_000703b4;
      fVar45 = (fVar47 + fVar48 + fVar5) * DAT_000703c0;
      pfVar22[6] = (fVar37 + fVar35 + fVar3) * DAT_000703b8;
      pfVar22[7] = (fVar38 + fVar40 + fVar4) * DAT_000703bc;
    }
    pfVar22[8] = fVar45;
    pfVar22 = pfVar22 + 9;
  } while (piVar6 != piVar24);
  pfVar22 = local_154 + 3;
  pfVar9 = &local_9c;
  pfVar7 = pfVar9;
  pfVar10 = pfVar22;
  do {
    fVar39 = *pfVar16;
    *pfVar7 = 1.0;
    iVar8 = 1;
    pfVar19 = local_154 + 5;
    pfVar25 = pfVar16;
    pfVar14 = pfVar7;
    fVar45 = fVar39;
    while( 1 ) {
      while( 1 ) {
        while( 1 ) {
          fVar31 = pfVar25[1];
          if (iVar8 != 1) break;
          fVar46 = -fVar31 / fVar45;
          pfVar19[1] = fVar46;
          fVar45 = fVar45 * (-fVar46 * fVar46 + 1.0);
          fVar31 = -(pfVar25[2] + fVar31 * local_154[6]) / fVar45;
          pfVar14 = pfVar14 + 2;
          pfVar7[1] = local_154[6] + fVar31 * fVar46;
          pfVar25 = pfVar25 + 2;
          pfVar19 = pfVar19 + 2;
          iVar8 = 3;
          fVar45 = fVar45 * (-fVar31 * fVar31 + 1.0);
          *pfVar14 = fVar31;
        }
        fVar35 = pfVar7[1];
        fVar29 = *pfVar25;
        fVar40 = pfVar7[2];
        fVar30 = pfVar25[-1];
        fVar46 = -fVar31 + -fVar35 * fVar29 + -fVar40 * fVar30;
        if (iVar8 == 3) {
          fVar46 = fVar46 / fVar45;
          fVar45 = (-fVar46 * fVar46 + 1.0) * fVar45;
          local_154[6] = fVar35 + fVar46 * *pfVar14;
          local_154[7] = fVar40 + fVar46 * pfVar14[-1];
        }
        else {
          fVar46 = fVar46 + -pfVar7[3] * pfVar25[-2] + -pfVar25[-3] * pfVar7[4];
          if (iVar8 != 5) {
            fVar46 = fVar46 + -pfVar7[5] * pfVar25[-4] + -pfVar25[-5] * pfVar7[6];
          }
          fVar46 = fVar46 / fVar45;
          fVar45 = fVar45 * (-fVar46 * fVar46 + 1.0);
          local_154[6] = fVar35 + *pfVar14 * fVar46;
          local_154[7] = fVar40 + pfVar14[-1] * fVar46;
          local_154[8] = pfVar7[3] + pfVar14[-2] * fVar46;
          local_154[9] = pfVar7[4] + pfVar14[-3] * fVar46;
          if (iVar8 != 5) {
            local_12c = pfVar7[5] + fVar46 * pfVar14[-4];
            local_128 = pfVar7[6] + pfVar14[-5] * fVar46;
          }
        }
        pfVar19[1] = fVar46;
        fVar40 = local_124;
        fVar35 = local_128;
        fVar31 = -(pfVar25[2] + fVar31 * local_154[6]) + -fVar29 * local_154[7] +
                 -fVar30 * local_154[8];
        if ((iVar8 != 3) &&
           (fVar31 = fVar31 + -pfVar25[-2] * local_154[9] + -pfVar25[-3] * local_12c, iVar8 != 5)) {
          fVar31 = fVar31 + -pfVar25[-4] * local_128 + -pfVar25[-5] * local_124;
        }
        fVar31 = fVar31 / fVar45;
        fVar29 = *pfVar19;
        fVar30 = pfVar19[-1];
        fVar45 = (-fVar31 * fVar31 + 1.0) * fVar45;
        pfVar7[1] = local_154[6] + fVar31 * fVar46;
        pfVar7[2] = local_154[7] + fVar31 * fVar29;
        pfVar7[3] = local_154[8] + fVar31 * fVar30;
        if (iVar8 != 3) break;
        pfVar14 = pfVar14 + 2;
        iVar8 = 5;
        pfVar25 = pfVar25 + 2;
        pfVar19 = pfVar19 + 2;
        *pfVar14 = fVar31;
      }
      fVar46 = pfVar19[-3];
      pfVar7[4] = local_154[9] + fVar31 * pfVar19[-2];
      pfVar7[5] = local_12c + fVar31 * fVar46;
      if (iVar8 != 5) break;
      pfVar14 = pfVar14 + 2;
      iVar8 = 7;
      pfVar25 = pfVar25 + 2;
      pfVar19 = pfVar19 + 2;
      *pfVar14 = fVar31;
    }
    fVar46 = pfVar19[-4];
    fVar29 = pfVar19[-5];
    *pfVar10 = fVar39 / fVar45;
    pfVar10 = pfVar10 + 1;
    pfVar7[6] = fVar35 + fVar31 * fVar46;
    pfVar7[7] = fVar40 + fVar31 * fVar29;
    pfVar16 = pfVar16 + 9;
    pfVar14[2] = fVar31;
    pfVar7 = pfVar7 + 9;
  } while (pfVar10 != pfVar22 + iVar20);
  piVar24 = param_5 + 1;
  pfVar16 = local_e4;
  puVar28 = (uint *)(param_5 + 3);
  iVar13 = 0;
  iVar8 = iVar20;
  piVar6 = piVar24;
  pfVar7 = pfVar16;
  do {
    piVar6 = piVar6 + 1;
    *piVar6 = 0;
    iVar21 = DAT_000709cc;
    fVar45 = DAT_000709c8;
    if ((param_3 == 0) && (fVar39 = *pfVar9, !(fVar39 <= 1.5f))) {
      fVar30 = pfVar9[1];
      fVar29 = pfVar9[2];
      fVar46 = pfVar9[3];
      fVar31 = pfVar9[4];
      fVar35 = pfVar9[5];
      fVar40 = pfVar9[6];
      fVar48 = pfVar9[7];
      fVar42 = pfVar9[8];
      if (((char)param_5[1] != '\0') && (fVar39 < 2.0f)) {
        fVar43 = (fVar39 - 2.0) * DAT_000709d0 + 1.0;
        fVar39 = fVar43 * fVar43 * fVar43;
        fVar29 = fVar29 * fVar43 * fVar43;
        fVar32 = fVar43 * fVar39;
        fVar46 = fVar46 * fVar39;
        fVar39 = fVar43 * fVar32;
        fVar31 = fVar31 * fVar32;
        fVar32 = fVar43 * fVar39;
        fVar30 = fVar30 * fVar43;
        fVar44 = fVar43 * fVar32;
        fVar35 = fVar35 * fVar39;
        fVar40 = fVar40 * fVar32;
        fVar48 = fVar48 * fVar44;
        fVar42 = fVar43 * fVar42 * fVar44;
        pfVar9[1] = fVar30;
        pfVar9[2] = fVar29;
        pfVar9[3] = fVar46;
        pfVar9[4] = fVar31;
        pfVar9[5] = fVar35;
        pfVar9[6] = fVar40;
        pfVar9[7] = fVar48;
        pfVar9[8] = fVar42;
      }
      pfVar7[7] = fVar42;
      fVar39 = 1.0 / (-fVar42 * fVar42 + 1.0);
      pfVar10 = pfVar7 + 7;
      iVar8 = 0x18;
      uVar11 = 6;
      local_100 = (fVar30 + -fVar42 * fVar48) * fVar39;
      local_fc = (fVar29 + -fVar42 * fVar40) * fVar39;
      local_f8 = (fVar46 + -fVar42 * fVar35) * fVar39;
      local_f4 = (1.0 - fVar42) * fVar31 * fVar39;
      local_f0 = (fVar35 + -fVar42 * fVar46) * fVar39;
      local_ec = (fVar40 + -fVar42 * fVar29) * fVar39;
      local_e8 = (fVar48 + -fVar42 * fVar30) * fVar39;
      pfVar19 = local_11c + 7;
      while( 1 ) {
        pfVar25 = (float *)((int)pfVar19 + iVar8);
        fVar46 = *pfVar25;
        fVar39 = 1.0 / (-fVar46 * fVar46 + 1.0);
        fVar31 = fVar39 * (*pfVar19 + -fVar46 * pfVar25[-1]);
        uVar17 = uVar11 & 1;
        pfVar10 = pfVar10 + -1;
        *pfVar10 = fVar46;
        local_11c[uVar17 * 7] = fVar31;
        fVar46 = -fVar46;
        if (uVar11 == 1) break;
        local_11c[uVar17 * 7 + 1] = fVar39 * (pfVar19[1] + fVar46 * pfVar25[-2]);
        if ((((uVar11 != 2) &&
             (local_11c[uVar17 * 7 + 2] = fVar39 * (pfVar19[2] + fVar46 * pfVar25[-3]), uVar11 != 3)
             ) && (local_11c[uVar17 * 7 + 3] = fVar39 * (pfVar19[3] + fVar46 * pfVar25[-4]),
                  uVar11 != 4)) &&
           (local_11c[uVar17 * 7 + 4] = fVar39 * (pfVar19[4] + fVar46 * pfVar25[-5]), uVar11 == 6))
        {
          local_11c[uVar17 * 7 + 5] = (pfVar19[5] + fVar46 * pfVar25[-6]) * fVar39;
        }
        uVar11 = uVar11 - 1;
        iVar8 = iVar8 + -4;
        pfVar19 = local_11c + uVar17 * 7;
      }
      *pfVar7 = fVar31;
      *piVar6 = 8;
      puVar23 = puVar28;
      pfVar10 = pfVar7;
      do {
        fVar31 = *pfVar10;
        pfVar10 = pfVar10 + 1;
        fVar46 = __builtin_fabsf(fVar31);
        uVar17 = (uint)(fVar46 >= fVar45);
        fVar39 = *(float *)(iVar21 + uVar17 * 0x10);
        uVar11 = uVar17 * 4;
        puVar23 = puVar23 + 1;
        *puVar23 = uVar11;
        if (!(fVar46 >= fVar39)) {
          if (fVar31 < 0.0f) {
            uVar11 = uVar17 * -4;
            *puVar23 = uVar11;
          }
          if (uVar11 != 0) goto LAB_000708d4;
          iVar18 = *piVar6 + -1;
        }
        else {
          uVar17 = uVar11 + 1;
          fVar39 = *(float *)(iVar21 + uVar17 * 4);
          *puVar23 = uVar17;
          if (!(fVar46 < fVar39)) {
            uVar17 = uVar11 + 2;
            fVar39 = *(float *)(iVar21 + uVar17 * 4);
            *puVar23 = uVar17;
            if (!(fVar46 < fVar39)) {
              uVar17 = uVar11 + 3;
              fVar39 = *(float *)(iVar21 + uVar17 * 4);
              *puVar23 = uVar17;
              if (!(fVar46 < fVar39)) {
                uVar17 = uVar11 + 4;
                *puVar23 = uVar17;
              }
            }
          }
          if (fVar31 < 0.0f) {
            *puVar23 = -uVar17;
          }
LAB_000708d4:
          iVar18 = 8;
        }
        *piVar6 = iVar18;
      } while (pfVar7 + 8 != pfVar10);
      iVar8 = *param_5;
      if (0 < iVar18) {
        puVar23 = puVar28;
        pfVar10 = pfVar7;
        do {
          puVar23 = puVar23 + 1;
          uVar11 = *puVar23;
          fVar45 = *(float *)(DAT_000709d4 +
                             ((uVar11 ^ (int)uVar11 >> 0x1f) - ((int)uVar11 >> 0x1f)) * 4);
          if ((int)uVar11 < 0) {
            fVar45 = -fVar45;
          }
          *pfVar10 = fVar45;
          pfVar10 = pfVar10 + 1;
        } while (puVar23 != puVar28 + iVar18);
      }
    }
    pfVar7 = pfVar7 + 8;
    iVar13 = iVar13 + 1;
    pfVar22 = pfVar22 + 1;
    puVar28 = puVar28 + 8;
    pfVar9 = pfVar9 + 9;
    if (iVar8 <= iVar13) {
      param_1 = param_1 + 3;
      iVar13 = (int)((param_2 * param_1 + param_1) * 0x14) >> (uint)(2 < param_2);
      piVar6 = piVar24 + iVar20;
      pfVar22 = (float *)(param_6 + iVar13 * 4);
      iVar20 = iVar13;
      iVar8 = param_1 * 3;
      fVar45 = DAT_0007039c;
      fVar39 = DAT_0007039c;
      fVar31 = DAT_0007039c;
      fVar46 = DAT_0007039c;
      fVar29 = DAT_0007039c;
      fVar30 = DAT_0007039c;
      fVar35 = DAT_0007039c;
      fVar40 = DAT_0007039c;
      do {
        iVar21 = iVar20;
        piVar24 = piVar24 + 1;
        iVar20 = *piVar24;
        if ((iVar20 != 0) && (iVar8 < iVar21)) {
          pfVar9 = (float *)(param_6 + iVar8 * 4);
          while( 1 ) {
            fVar42 = *pfVar9;
            fVar48 = fVar42;
            if (0 < iVar20) {
              fVar32 = fVar40 + *pfVar16 * fVar42;
              fVar48 = fVar42 + *pfVar16 * fVar40;
              fVar40 = fVar42;
              if (iVar20 != 1) {
                fVar42 = fVar35 + fVar48 * pfVar16[1];
                fVar48 = fVar48 + pfVar16[1] * fVar35;
                fVar35 = fVar32;
                if (iVar20 != 2) {
                  fVar32 = fVar30 + fVar48 * pfVar16[2];
                  fVar48 = fVar48 + fVar30 * pfVar16[2];
                  fVar30 = fVar42;
                  if (iVar20 != 3) {
                    fVar42 = fVar46 + fVar48 * pfVar16[3];
                    fVar48 = fVar48 + fVar46 * pfVar16[3];
                    fVar46 = fVar32;
                    if (iVar20 != 4) {
                      fVar32 = fVar31 + fVar48 * pfVar16[4];
                      fVar48 = fVar48 + fVar31 * pfVar16[4];
                      fVar31 = fVar42;
                      if (iVar20 != 5) {
                        fVar42 = fVar39 + pfVar16[5] * fVar48;
                        fVar48 = fVar48 + fVar39 * pfVar16[5];
                        fVar39 = fVar32;
                        if (iVar20 != 6) {
                          fVar32 = fVar29 + pfVar16[6] * fVar48;
                          fVar48 = fVar48 + fVar29 * pfVar16[6];
                          fVar29 = fVar42;
                          if (iVar20 != 7) {
                            fVar42 = pfVar16[7] * fVar45;
                            fVar45 = fVar32;
                            fVar48 = fVar48 + fVar42;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            *pfVar9 = fVar48;
            if (pfVar9 + 1 == pfVar22) break;
            iVar20 = *piVar24;
            pfVar9 = pfVar9 + 1;
          }
        }
        pfVar22 = pfVar22 + iVar13;
        pfVar16 = pfVar16 + 8;
        iVar20 = iVar21 + iVar13;
        iVar8 = iVar21;
      } while (piVar6 != piVar24);
      return;
    }
  } while( 1 );
}
