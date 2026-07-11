/* Reconstructed FUN_0006f9c0 @ 0x6f9c0  (parity: 119/300 trials, PROVEN) */
#include <stdint.h>

static inline float fabsf(float x){ union{float f; uint32_t u;} v; v.f=x; v.u&=0x7fffffffu; return v.f; }

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

#define SBORROW4(a,b) ((int)((((uint)(a)^(uint)(b)) & ((uint)(a)^((uint)(a)-(uint)(b)))) ) < 0)
#define VU(a) (*(volatile uint*)(a))

extern uint FUN_00068590(int);
extern void FUN_00068908(int,...);
extern void FUN_0006897c(int);

void FUN_0006f9c0(int param_1,int param_2,int param_3,int param_4,int param_5,
                  volatile ushort *param_6,int param_7,volatile float *param_8)
{
  ushort uVar1, uVar2;
  volatile ushort *puVar3;
  uint uVar4;
  volatile float *pfVar5;
  uint uVar6, uVar7, uVar9, uVar10, uVar11, uVar14, uVar16, uVar19, uVar20;
  int iVar8, iVar12, iVar13, iVar15, iVar17, iVar18, iVar22, iVar23, iVar24;
  volatile byte *pbVar21;
  int bVar25, bVar26;
  float fVar27, fVar28;
  uint local_50; int local_4c; uint local_40; int local_3c;

  uVar14 = (uint)*(volatile byte*)(param_7 + 8);
  iVar15 = *(volatile int*)(param_7 + 4);
  param_4 = param_4 + 1;
  iVar24 = iVar15;
  fVar27 = 0.0f;
  if (param_2 == 0) {
    iVar8 = param_4 * 0x3c;
    if ((iVar15 + param_4 * -0x3c < 0) == SBORROW4(iVar15,iVar8)) iVar24 = iVar8;
    iVar8 = iVar8 + 2;
    if (0x10 < iVar24) {
      iVar13 = 0x10; iVar18 = 3; iVar23 = 2;
      goto LAB_fa00;
    }
    iVar18 = 3; iVar22 = 0x10; iVar24 = 4; param_2 = -2; iVar13 = 0; iVar17 = 0;
LAB_fa6c:
    pfVar5 = param_8 + param_2 + iVar22;
    iVar22 = iVar22 - iVar13;
    do {
      iVar13 = iVar13 + 1;
      if (iVar24 < iVar13) { fVar27 = fVar27 + fabsf(*pfVar5); iVar17 = iVar17 + 1; }
      pfVar5 = pfVar5 + 1;
    } while (iVar22 + iVar13 < iVar8);
LAB_fa98:
    if (iVar17 != 0) {
      uVar9 = VU(param_1 + 0x20);
      iVar24 = -(int)((fVar27 * 16.0f) / (float)iVar17 + 0.5f);
      uVar6 = iVar24 + 8;
      bVar26 = SBORROW4(uVar6,6);
      bVar25 = uVar6 == 6;
      if (6 < (int)uVar6) uVar6 = 7;
      if (bVar25 || ((iVar24 + 2 < 0) != bVar26)) uVar6 = uVar6 & ~((int)uVar6 >> 0x1f);
      goto joined;
    }
  }
  else {
    iVar8 = param_4 * 0x50;
    if ((iVar15 + param_4 * -0x50 < 0) == SBORROW4(iVar15,iVar8)) iVar24 = iVar8;
    iVar18 = param_2 + 3;
    iVar23 = param_2 + 2;
    iVar22 = iVar18 * 6 - iVar23;
    iVar8 = iVar8 + iVar23;
    iVar13 = iVar22;
    if (iVar22 < iVar24) {
LAB_fa00:
      iVar22 = iVar24;
      iVar17 = 0;
      param_2 = -2 - param_2;
      puVar3 = param_6 + iVar13 + 0x7fffffff;
      pfVar5 = param_8 + iVar13 + param_2;
      iVar12 = 0;
      iVar24 = iVar23 * 2;
      do {
        while (1) {
          puVar3 = puVar3 + 1;
          iVar12 = iVar12 + 1;
          if (*puVar3 == 0) break;
          iVar12 = 0;
          pfVar5 = pfVar5 + 1;
          iVar13 = 0;
          if (puVar3 == param_6 + iVar22 + -1) goto LAB_fa66;
        }
        if (iVar12 != iVar24 && ((iVar12 + iVar23 * -2 < 0) == SBORROW4(iVar12,iVar24))) {
          fVar27 = fVar27 + fabsf(*pfVar5); iVar17 = iVar17 + 1;
        }
        pfVar5 = pfVar5 + 1;
        iVar13 = iVar12;
      } while (puVar3 != param_6 + iVar22 + -1);
LAB_fa66:
      if (iVar22 < iVar8) goto LAB_fa6c;
      goto LAB_fa98;
    }
    if (iVar22 < iVar8) {
      iVar13 = 0; iVar24 = iVar23 * 2; param_2 = -2 - param_2; iVar17 = iVar13;
      goto LAB_fa6c;
    }
  }
  uVar9 = VU(param_1 + 0x20);
  uVar6 = 0;
joined:
  if ((int)(uVar9 + 3) < 0x21) {
    VU(param_1 + 0x20) = uVar9 + 3;
    VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | uVar6 << (uVar9 & 0xff);
  }
  else {
    FUN_00068908(param_1, uVar6, 3);
  }
  iVar8 = 0x8dc50;
  iVar24 = (param_3 + 1) * 0x14;
  local_4c = 0x8ed50 +
             (uint)(param_5 != iVar24 &&
                   ((param_5 + (param_3 + 1) * -0x14 < 0) == SBORROW4(param_5,iVar24))) * 0x800;
  local_50 = 0;
  local_3c = 0;
  local_40 = 1;
  do {
    iVar24 = (param_3 * iVar18 + iVar18) * 0x14 + 2 >> (local_40 & 0xff);
    if (iVar15 <= iVar24) iVar24 = iVar15;
    if (local_3c < iVar24) {
      uVar9 = (iVar24 - local_3c) - 1;
      puVar3 = param_6 + local_3c;
LAB_fb52:
      do {
        uVar19 = (uint)(puVar3[1] >> 1);
        uVar16 = ((uint)(ushort)((puVar3[1] | *puVar3) >> 1) << 0x10) >> 0x12;
        uVar6 = (uint)(*puVar3 >> 1);
        pbVar21 = (volatile byte *)(local_4c + local_50 * 4);
        if (uVar16 == 0) {
          uVar16 = 0; uVar20 = uVar19; uVar10 = uVar6;
        }
        else {
          uVar20 = uVar14; uVar10 = uVar14;
          if (uVar14 == 0) {
LAB_fd54:
            do {
              while (1) {
                uVar4 = VU(param_1 + 0x20);
                uVar11 = uVar4 + 1;
                uVar7 = (int)uVar6 >> (uVar20 & 0xff) & 1;
                if ((int)uVar11 < 0x21) {
                  VU(param_1 + 0x20) = uVar11;
                  VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | uVar7 << (uVar4 & 0xff);
                }
                else {
                  FUN_00068908(param_1, uVar7, 1);
                  uVar11 = VU(param_1 + 0x20);
                }
                uVar4 = (int)uVar19 >> (uVar20 & 0xff) & 1;
                if ((int)(uVar11 + 1) < 0x21) {
                  VU(param_1 + 0x20) = uVar11 + 1;
                  VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | uVar4 << (uVar11 & 0xff);
                }
                else {
                  FUN_00068908(param_1, uVar4, 1);
                }
                uVar4 = uVar20;
                if (2 < (int)uVar20) uVar4 = 3;
                uVar7 = VU(param_1 + 8) >> 10;
                iVar24 = iVar8 + (uint)pbVar21[uVar4] * 0x44;
                uVar4 = uVar7 * *(volatile ushort *)(iVar24 + 0x40) + VU(param_1 + 4);
                VU(param_1 + 4) = uVar4;
                uVar7 = uVar7 * *(volatile ushort *)(iVar24 + 0x42);
                VU(param_1 + 4) = uVar4 & 0xffffff;
                VU(param_1 + 8) = uVar7;
                uVar20 = uVar20 + 1;
                VU(param_1 + 0x10) = VU(param_1 + 0x10) | uVar4 >> 0x18;
                uVar16 = (int)uVar16 >> 1;
                if (uVar7 < 0x10000) break;
                if (uVar16 == 0) goto LAB_fd7e;
              }
              FUN_0006897c(param_1);
            } while (uVar16 != 0);
LAB_fd7e:
            uVar16 = uVar20;
            if (2 < (int)uVar20) uVar16 = 3;
          }
          else {
            iVar24 = iVar8 + (uint)*pbVar21 * 0x44;
            uVar20 = VU(param_1 + 8) >> 10;
            uVar10 = uVar20 * *(volatile ushort *)(iVar24 + 0x40) + VU(param_1 + 4);
            VU(param_1 + 4) = uVar10;
            uVar20 = uVar20 * *(volatile ushort *)(iVar24 + 0x42);
            VU(param_1 + 8) = uVar20;
            VU(param_1 + 0x10) = VU(param_1 + 0x10) | uVar10 >> 0x18;
            VU(param_1 + 4) = uVar10 & 0xffffff;
            if (uVar20 < 0x10000) FUN_0006897c(param_1);
            uVar16 = (int)uVar16 >> 1;
            if (uVar16 != 0) { uVar20 = 1; uVar10 = uVar20; goto LAB_fd54; }
            uVar10 = 1; uVar16 = uVar10; uVar20 = uVar10;
          }
          pbVar21 = pbVar21 + uVar16;
          uVar4 = (int)uVar6 >> uVar10;
          uVar7 = (int)uVar19 >> uVar10;
          uVar6 = (int)uVar4 >> (uVar20 - uVar10 & 0xff);
          uVar19 = (int)uVar7 >> (uVar20 - uVar10 & 0xff);
          uVar20 = uVar7 & 0xffff;
          uVar10 = uVar4 & 0xffff;
        }
        if (uVar10 != 0) {
          uVar10 = VU(param_1 + 0x20);
          uVar2 = *puVar3;
          iVar24 = uVar10 + 1;
          if (iVar24 < 0x21) {
            VU(param_1 + 0x20) = iVar24;
            VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | (uVar2 & 1) << (uVar10 & 0xff);
          }
          else {
            FUN_00068908(param_1, uVar2 & 1, 1);
          }
        }
        if (uVar20 != 0) {
          uVar20 = VU(param_1 + 0x20);
          uVar2 = puVar3[1];
          iVar24 = uVar20 + 1;
          if (iVar24 < 0x21) {
            VU(param_1 + 0x20) = iVar24;
            VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | (uVar2 & 1) << (uVar20 & 0xff);
          }
          else {
            FUN_00068908(param_1, uVar2 & 1, 1);
          }
        }
        iVar24 = uVar6 + uVar19 * 4;
        iVar13 = iVar8 + (uint)*pbVar21 * 0x44;
        uVar20 = VU(param_1 + 8) >> 10;
        uVar10 = uVar20 * *(volatile ushort *)(iVar13 + iVar24 * 4) + VU(param_1 + 4);
        VU(param_1 + 4) = uVar10;
        uVar20 = uVar20 * *(volatile ushort *)(iVar13 + iVar24 * 4 + 2);
        VU(param_1 + 8) = uVar20;
        VU(param_1 + 0x10) = VU(param_1 + 0x10) | uVar10 >> 0x18;
        VU(param_1 + 4) = uVar10 & 0xffffff;
        if (uVar20 < 0x10000) FUN_0006897c(param_1);
        iVar24 = (local_50 & 0xf) * 0x10;
        if (1 < (int)uVar16) {
          local_50 = iVar24 + uVar16 + 0xc & 0xff;
          puVar3 = puVar3 + 2;
          if (param_6 + (uVar9 & 0xfffffffe) + local_3c + 2 == puVar3) break;
          goto LAB_fb52;
        }
        local_50 = (int)(short)((short)uVar6 + (short)uVar19) * (int)(short)((short)uVar16 + 1) +
                   iVar24 + 1U & 0xff;
        puVar3 = puVar3 + 2;
      } while (puVar3 != param_6 + (uVar9 & 0xfffffffe) + local_3c + 2);
      local_3c = (uVar9 & 0xfffffffe) + local_3c + 2;
    }
    local_4c = local_4c + 0x400;
    bVar25 = local_40 == 0;
    local_40 = local_40 - 1;
    if (bVar25) {
      iVar24 = (int)FUN_00068590(param_1);
      if (uVar14 == 0) {
        if ((0 < iVar15) && (0 < iVar24)) {
          param_6 = param_6 + -1;
          puVar3 = param_6 + iVar15;
          while (1) {
            while (1) {
              param_6 = param_6 + 1;
              uVar2 = *param_6;
              if (uVar2 == 0) break;
              uVar14 = (uint)(uVar2 >> 1);
              if ((int)((uint)uVar2 << 0x1f) < 0) uVar14 = -uVar14;
              fVar27 = *param_8;
              fVar28 = (float)(int)uVar14;
              {
                int bit = (fVar27 >= fVar28) ? 1 : 0;
                uVar9 = VU(param_1 + 0x20);
                iVar15 = uVar9 + 1;
                if (iVar15 < 0x21) {
                  uVar14 = bit << (uVar9 & 0xff);
                  VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | uVar14;
                  VU(param_1 + 0x20) = iVar15;
                }
                else {
                  FUN_00068908(param_1, bit, 1);
                }
              }
              iVar24 = iVar24 + -1;
              if (param_6 == puVar3) return;
              param_8 = param_8 + 1;
              if (iVar24 == 0) return;
            }
            if (param_6 == puVar3) break;
            param_8 = param_8 + 1;
          }
        }
      }
      else if ((0 < iVar15) && (0 < iVar24)) {
        puVar3 = param_6 + (iVar15 - 1U & 0xfffffffe);
        while (1) {
          while (1) {
            uVar1 = param_6[1];
            uVar2 = *param_6;
            if (((uint)(ushort)((uVar1 | uVar2) >> 1) << 0x10) >> 0x12 != 0) break;
            if (param_6 == puVar3) return;
            param_6 = param_6 + 2;
          }
          uVar14 = VU(param_1 + 0x20);
          iVar8 = iVar24 + -1;
          iVar15 = uVar14 + 1;
          uVar9 = uVar2 >> 1 & 1;
          if (iVar15 < 0x21) {
            VU(param_1 + 0x20) = iVar15;
            VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | uVar9 << (uVar14 & 0xff);
          }
          else {
            FUN_00068908(param_1, uVar9, 1);
          }
          if (uVar2 >> 1 == 1) {
            if (iVar8 == 0) return;
            uVar14 = VU(param_1 + 0x20);
            iVar15 = uVar14 + 1;
            if (iVar15 < 0x21) {
              VU(param_1 + 0x20) = iVar15;
              VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | (uVar2 & 1) << (uVar14 & 0xff);
            }
            else {
              FUN_00068908(param_1, uVar2 & 1, 1);
            }
            iVar8 = iVar24 + -2;
          }
          iVar24 = iVar8 + -1;
          if (iVar8 != 0) {
            uVar14 = VU(param_1 + 0x20);
            uVar9 = uVar1 >> 1 & 1;
            iVar15 = uVar14 + 1;
            if (iVar15 < 0x21) {
              VU(param_1 + 0x20) = iVar15;
              VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | uVar9 << (uVar14 & 0xff);
            }
            else {
              FUN_00068908(param_1, uVar9, 1);
            }
          }
          if (uVar1 >> 1 == 1) {
            if (0 < iVar24) {
              uVar14 = VU(param_1 + 0x20);
              iVar24 = uVar14 + 1;
              if (iVar24 < 0x21) {
                VU(param_1 + 0x20) = iVar24;
                VU(param_1 + 0x1c) = VU(param_1 + 0x1c) | (uVar1 & 1) << (uVar14 & 0xff);
              }
              else {
                FUN_00068908(param_1, uVar1 & 1, 1);
              }
            }
            iVar24 = iVar8 + -2;
          }
          if (param_6 == puVar3) break;
          param_6 = param_6 + 2;
          if (iVar24 < 1) return;
        }
        return;
      }
      return;
    }
  } while (1);
}

