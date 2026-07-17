/* Reconstructed FUN_00078110 @ 0x78110  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte;
typedef unsigned int uint;

extern int FUN_0000ef12(int);
extern void FUN_00076a94(int,...) __attribute__((noreturn));
extern int FUN_000785d4(int,...);
extern int FUN_00078654(int,...);
extern int FUN_000789f0(int,...);
extern int FUN_00086c04(int,...);
extern int FUN_00087036(void*,int,int);
extern int FUN_0008729e(int,int);
extern int FUN_00087340(int,...);
extern int FUN_00087510(unsigned);
extern int FUN_0008768e(int,int);

byte *FUN_00078110(int param_1, int *param_2, int *param_3, int *param_4, int *param_5, uint param_6)
{
  byte bVar2;
  int iVar6, iVar7, iVar8, iVar13, iVar17;
  uint uVar3, uVar9, uVar22, uVar23;
  byte *pbVar10, *pbVar12, *pbVar18, *pbVar19, *pbVar21;
  byte *fraction_start;
  uint *puVar20, *local_40;
  int *piVar14, *piVar15;
  int bVar4, bVar5;
  int uVar11;
  uint32_t scale = 0;
  int32_t precision;
  uint32_t status_base;

  iVar13 = *(volatile int*)0x98768UL;
  iVar6 = FUN_0000ef12(iVar13);
  bVar2 = *(volatile byte*)(iVar13 + iVar6 - 1);
  pbVar21 = (byte*)(*param_2 + 2);
  do {
    pbVar19 = pbVar21;
    pbVar21 = pbVar19 + 1;
  } while (*pbVar19 == 0x30);
  int leading_zero_count = (int)((uintptr_t)pbVar19 -
                                 ((uintptr_t)(uint32_t)*param_2 + 2u));
  iVar7 = FUN_00087340(*pbVar19);
  if (iVar7 == 0) {
    iVar7 = FUN_00087036(pbVar19, iVar13, iVar6);
    pbVar18 = pbVar19;
    if (iVar7 == 0) {
      fraction_start = pbVar19 + iVar6;
      iVar7 = FUN_00087340(pbVar19[iVar6]);
      pbVar12 = fraction_start;
      pbVar18 = fraction_start;
      if (iVar7 != 0) {
        do {
          pbVar19 = pbVar12;
          pbVar12 = pbVar19 + 1;
        } while (*pbVar19 == 0x30);
        iVar7 = FUN_00087340(0);
        pbVar21 = (byte*)0x1;
        bVar4 = iVar7 == 0;
        pbVar12 = pbVar19;
        goto LAB_00078192;
      }
    }
    fraction_start = 0;
    bVar4 = 1;
  } else {
    bVar4 = 0;
    fraction_start = 0;
    pbVar12 = pbVar19;
LAB_00078192:
    do {
      pbVar18 = pbVar12;
      pbVar12 = pbVar18 + 1;
      iVar7 = FUN_00087340(*pbVar18);
    } while (iVar7 != 0);
    iVar7 = FUN_00087036(pbVar18, iVar13, iVar6);
    if (iVar7 == 0) {
      if (fraction_start == 0) {
        fraction_start = pbVar18 + iVar6;
        pbVar12 = fraction_start;
        do {
          pbVar18 = pbVar12;
          pbVar12 = pbVar18 + 1;
          iVar7 = FUN_00087340(*pbVar18);
        } while (iVar7 != 0);
      }
    } else if (fraction_start == 0) goto LAB_000781d2;
    scale = (uint32_t)((uintptr_t)fraction_start - (uintptr_t)pbVar18) * 4u;
  }
LAB_000781d2:
  pbVar12 = pbVar18;
  if ((*pbVar18 & 0xdf) == 0x50) {
    if (pbVar18[1] == 0x2b) {
      bVar5 = 0;
      pbVar10 = pbVar18 + 2;
    } else if (pbVar18[1] == 0x2d) {
      bVar5 = 1;
      pbVar10 = pbVar18 + 2;
    } else {
      pbVar10 = pbVar18 + 1;
      bVar5 = 0;
    }
    uint32_t rlo;
    rlo = FUN_00087340(*pbVar10);
    if (((rlo - 1U) & 0xff) < 0x19) {
      byte *pp = pbVar10;
      uint32_t exponent_value = rlo - 0x10u;
      for (;;) {
        pp++;
        rlo = FUN_00087340(*pp);
        pbVar12 = pp;
        if (0x18 < ((rlo - 1U) & 0xff)) break;
        exponent_value = exponent_value * 10u + (rlo - 0x10u);
      }
      uint32_t exponent_delta = bVar5 ? 0u - exponent_value : exponent_value;
      scale += exponent_delta;
    }
  }
  *param_2 = (int32_t)(uintptr_t)pbVar12;
  if (bVar4) {
    if (leading_zero_count != 0) return (byte*)0x0;
    return (byte*)0x6;
  }
  int32_t digit_count_minus_one =
      (int32_t)((uintptr_t)pbVar18 - (uintptr_t)pbVar19) - 1;
  iVar7 = 0;
LAB_00078258:
  if (7 < digit_count_minus_one) {
    iVar7 = iVar7 + 1;
    digit_count_minus_one >>= 1;
    goto LAB_00078258;
  }
  iVar7 = FUN_000785d4(param_1, iVar7);
  if (iVar7 == 0) {
    uVar11 = 0xde;
    FUN_00076a94(0xf8c53, uVar11, 0);
  }
  uVar23 = 0;
  puVar20 = (uint*)(iVar7 + 0x14);
  uVar22 = 0;
  local_40 = puVar20;
  while (pbVar21 = pbVar18, pbVar19 < pbVar21) {
    if (((pbVar21[-1] != bVar2) || (pbVar18 = pbVar21 + -1 + (1 - iVar6), pbVar18 < pbVar19)) ||
        (iVar8 = FUN_00087036(pbVar18, iVar13, iVar6), iVar8 != 0)) {
      if (uVar23 == 0x20) {
        *local_40 = uVar22;
        uVar22 = 0;
        uVar23 = 0;
        local_40 = local_40 + 1;
      }
      uVar9 = FUN_00087340(pbVar21[-1]);
      uVar3 = uVar23 & 0xff;
      uVar23 = uVar23 + 4;
      uVar22 = uVar22 | (uVar9 & 0xf) << uVar3;
      pbVar18 = pbVar21 - 1;
    }
  }
  *local_40 = uVar22;
  iVar17 = (int)(local_40 - puVar20) + 1;
  *(volatile int*)(iVar7 + 0x10) = iVar17;
  iVar8 = FUN_00087510(uVar22);
  precision = *param_3;
  iVar8 = iVar17 * 0x20 - iVar8;
  if (precision < iVar8) {
    iVar8 = iVar8 - precision;
    uVar22 = FUN_0008768e(iVar7, iVar8);
    if (uVar22 != 0) {
      uVar23 = iVar8 - 1;
      uVar22 = 1;
      if ((1u << (uVar23 & 0x1f) & puVar20[(int)uVar23 >> 5]) != 0) {
        if (((int)uVar23 < 2) || (iVar17 = FUN_0008768e(iVar7, iVar8 - 2), iVar17 == 0)) {
          uVar22 = 2;
        } else {
          uVar22 = 3;
        }
      }
    }
    scale += (uint32_t)iVar8;
    FUN_0008729e(iVar7, iVar8);
  } else {
    if (iVar8 < precision) {
      scale -= (uint32_t)(precision - iVar8);
      iVar7 = FUN_000789f0(param_1, iVar7, precision - iVar8);
      puVar20 = (uint*)(iVar7 + 0x14);
    }
    uVar22 = 0;
  }
  iVar8 = iVar7;
  if (param_3[2] < (int32_t)scale) goto LAB_000782f2;
  if ((int32_t)scale < param_3[1]) {
    int32_t distance = param_3[1] - (int32_t)scale;
    if (precision <= distance) {
      iVar6 = param_3[3];
      if (iVar6 == 2) {
        if (param_6 != 0) goto LAB_000783e8;
      } else {
        if (iVar6 != 3) {
          if ((iVar6 != 1) || (precision != distance)) goto LAB_000783e8;
          if (precision == 1) goto LAB_000783b6;
          param_6 = FUN_0008768e(iVar7, precision - 1);
        }
        if (param_6 == 0) {
LAB_000783e8:
          FUN_00078654(param_1, iVar7);
          *param_5 = 0;
          return (byte*)0x50;
        }
      }
LAB_000783b6:
      *param_4 = param_3[1];
      *(volatile int*)(iVar7 + 0x10) = 1;
      *puVar20 = 1;
      *param_5 = iVar7;
      return (byte*)0x62;
    }
    int32_t shift_index = distance - 1;
    if (uVar22 == 0) {
      if (shift_index != 0) uVar22 = FUN_0008768e(iVar7, shift_index);
    } else {
      uVar22 = 1;
    }
    precision -= distance;
    status_base = 2;
    if ((1u << ((uint32_t)shift_index & 0x1f) &
         puVar20[(uint32_t)shift_index >> 5]) != 0) {
      uVar22 = uVar22 | 2;
    }
    FUN_0008729e(iVar7, distance);
    scale = param_3[1];
  } else {
    status_base = 1;
  }
  if (uVar22 == 0) goto LAB_000784da;
  iVar17 = param_3[3];
  if (iVar17 != 2) {
    uVar23 = param_6;
    if (iVar17 == 3) goto joined_r0x0007846c;
    if ((iVar17 == 1) && ((uVar22 & 2) != 0)) {
      uVar23 = (uVar22 | *puVar20) & 1;
      goto joined_r0x0007846c;
    }
LAB_0007846e:
    status_base |= 0x10;
    goto LAB_000784da;
  }
  param_6 = 1 - param_6;
  uVar23 = param_6;
joined_r0x0007846c:
  if (uVar23 == 0) goto LAB_0007846e;
  iVar17 = *(volatile int*)(iVar7 + 0x10);
  piVar14 = (int*)(iVar7 + 0x14);
  do {
    piVar15 = piVar14 + 1;
    if (*piVar14 != -1) {
      *piVar14 = *piVar14 + 1;
      goto LAB_000784b0;
    }
    *piVar14 = 0;
    piVar14 = piVar15;
  } while (piVar15 < (int*)(iVar7 + 0x14) + iVar17);
  if (*(volatile int*)(iVar7 + 8) <= iVar17) {
    iVar8 = FUN_000785d4(param_1, *(volatile int*)(iVar7 + 4) + 1);
    if (iVar8 == 0) {
      uVar11 = 0x84;
      FUN_00076a94(0xf8c42, uVar11, 0);
    }
    FUN_00086c04(iVar8 + 0xc, iVar7 + 0xc, (*(volatile int*)(iVar7 + 0x10) + 2) * 4);
    FUN_00078654(param_1, iVar7);
  }
  iVar6 = *(volatile int*)(iVar8 + 0x10);
  *(volatile int*)(iVar8 + 0x10) = iVar6 + 1;
  *(volatile int*)(iVar8 + iVar6 * 4 + 0x14) = 1;
LAB_000784b0:
  if (status_base == 2) {
    uVar22 = 2;
    if (((*param_3 - 1) != precision) ||
        ((1u << ((uint32_t)precision & 0x1f) &
          *(volatile uint*)(iVar8 + 0x14 + ((uint32_t)precision >> 5) * 4)) == 0))
      goto LAB_000784d6;
  } else if ((iVar17 < *(volatile int*)(iVar8 + 0x10)) ||
             ((((uint32_t)precision & 0x1f) != 0 &&
               (iVar6 = FUN_00087510(*(volatile int*)(iVar8 + 0x14 + iVar17 * 4 - 4)),
                iVar6 < (int)(0x20 - ((uint32_t)precision & 0x1f)))))) {
    FUN_0008729e(iVar8, 1);
    scale += 1u;
    if (param_3[2] < (int32_t)scale) {
LAB_000782f2:
      FUN_00078654(param_1, iVar8);
      *param_5 = 0;
      return (byte*)0xa3;
    }
  }
  uVar22 = 1;
LAB_000784d6:
  status_base = uVar22 | 0x20;
LAB_000784da:
  *param_5 = iVar8;
  *param_4 = (int32_t)scale;
  return (byte*)(uintptr_t)status_base;
}
