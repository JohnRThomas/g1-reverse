/* Reconstructed FUN_00078110 @ 0x78110  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte;
typedef unsigned int uint;

extern int FUN_0000ef12(int);
extern int FUN_00076a94(int,...);
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
  int extraout_r1 = 0;
  byte *pbVar10, *pbVar12, *pbVar16, *pbVar18, *pbVar19, *pbVar21;
  uint *puVar20, *local_40;
  int *piVar14, *piVar15;
  int bVar4, bVar5;
  int uVar11;

  iVar13 = *(volatile int*)0x98768UL;
  iVar6 = FUN_0000ef12(iVar13);
  bVar2 = *(volatile byte*)(iVar13 + iVar6 - 1);
  pbVar21 = (byte*)(*param_2 + 2);
  do {
    pbVar19 = pbVar21;
    pbVar21 = pbVar19 + 1;
  } while (*pbVar19 == 0x30);
  pbVar21 = pbVar19 + (-2 - *param_2);
  iVar7 = FUN_00087340(0);
  if (iVar7 == 0) {
    iVar7 = FUN_00087036(pbVar19, iVar13, iVar6);
    pbVar18 = pbVar19;
    if (iVar7 == 0) {
      pbVar16 = pbVar19 + iVar6;
      iVar7 = FUN_00087340(pbVar19[iVar6]);
      pbVar12 = pbVar16;
      pbVar18 = pbVar16;
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
    pbVar16 = 0;
    bVar4 = 1;
  } else {
    bVar4 = 0;
    pbVar16 = 0;
    pbVar12 = pbVar19;
LAB_00078192:
    do {
      pbVar18 = pbVar12;
      pbVar12 = pbVar18 + 1;
      iVar7 = FUN_00087340(*pbVar18);
    } while (iVar7 != 0);
    iVar7 = FUN_00087036(pbVar18, iVar13, iVar6);
    if (iVar7 == 0) {
      if (pbVar16 == 0) {
        pbVar16 = pbVar18 + iVar6;
        pbVar12 = pbVar16;
        do {
          pbVar18 = pbVar12;
          pbVar12 = pbVar18 + 1;
          iVar7 = FUN_00087340(*pbVar18);
        } while (iVar7 != 0);
      }
    } else if (pbVar16 == 0) goto LAB_000781d2;
    pbVar16 = (byte*)(((int)pbVar16 - (int)pbVar18) * 4);
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
    uint32_t rlo; int rhi;
    rlo = FUN_00087340(*pbVar10);
    rhi = 0;
    if (((rlo - 1U) & 0xff) < 0x19) {
      byte *pp = pbVar10;
      for (;;) {
        iVar7 = (int)rlo - 0x10;
        pp = pp + 1 + rhi;
        rlo = FUN_00087340(*pp);
        rhi = 0;
        pbVar12 = pp;
        if (0x18 < ((rlo - 1U) & 0xff)) break;
        rlo = iVar7 * 10 + (int)rlo;
      }
      if (bVar5) iVar7 = -iVar7;
      pbVar16 = pbVar16 + iVar7;
    }
  }
  *param_2 = (int)(long)pbVar12;
  if (bVar4) {
    if (pbVar21 != 0) return (byte*)0x0;
    return (byte*)0x6;
  }
  pbVar21 = pbVar18 + (-1 - (int)(long)pbVar19);
  iVar7 = 0;
LAB_00078258:
  if (7 < (int)(long)pbVar21) {
    iVar7 = iVar7 + 1;
    pbVar21 = (byte*)((int)(long)pbVar21 >> 1);
    goto LAB_00078258;
  }
  iVar7 = FUN_000785d4(param_1, iVar7);
  if (iVar7 == 0) {
    uVar11 = 0xde;
    FUN_00076a94(0xf8c53, uVar11, 0);
    iVar7 = extraout_r1;
    iVar7 = iVar7 + 1;
    goto LAB_00078258;
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
  iVar17 = ((int)(long)local_40 + (4 - (int)(long)puVar20)) >> 2;
  *(volatile int*)(iVar7 + 0x10) = iVar17;
  iVar8 = FUN_00087510(uVar22);
  pbVar19 = (byte*)*param_3;
  iVar8 = iVar17 * 0x20 - iVar8;
  if ((int)(long)pbVar19 < iVar8) {
    iVar8 = iVar8 - (int)(long)pbVar19;
    uVar22 = FUN_0008768e(iVar7, iVar8);
    if (uVar22 != 0) {
      uVar23 = iVar8 - 1;
      uVar22 = 1;
      if ((1 << (uVar23 & 0x1f) & puVar20[(int)uVar23 >> 5]) != 0) {
        if (((int)uVar23 < 2) || (iVar17 = FUN_0008768e(iVar7, iVar8 - 2), iVar17 == 0)) {
          uVar22 = 2;
        } else {
          uVar22 = 3;
        }
      }
    }
    pbVar16 = pbVar16 + iVar8;
    FUN_0008729e(iVar7, iVar8);
  } else {
    if (iVar8 < (int)(long)pbVar19) {
      pbVar16 = pbVar16 - ((int)(long)pbVar19 - iVar8);
      iVar7 = FUN_000789f0(param_1, iVar7, (int)(long)pbVar19 - iVar8);
      puVar20 = (uint*)(iVar7 + 0x14);
    }
    uVar22 = 0;
  }
  iVar8 = iVar7;
  if (param_3[2] < (int)(long)pbVar16) goto LAB_000782f2;
  if ((int)(long)pbVar16 < param_3[1]) {
    pbVar16 = (byte*)(long)(param_3[1] - (int)(long)pbVar16);
    if ((int)(long)pbVar19 <= (int)(long)pbVar16) {
      iVar6 = param_3[3];
      if (iVar6 == 2) {
        if (param_6 != 0) goto LAB_000783e8;
      } else {
        if (iVar6 != 3) {
          if ((iVar6 != 1) || (pbVar19 != pbVar16)) goto LAB_000783e8;
          if (pbVar19 == (byte*)0x1) goto LAB_000783b6;
          param_6 = FUN_0008768e(iVar7, (int)(long)(pbVar19 - 1));
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
    pbVar21 = pbVar16 - 1;
    if (uVar22 == 0) {
      if (pbVar21 != 0) uVar22 = FUN_0008768e(iVar7, (int)(long)pbVar21);
    } else {
      uVar22 = 1;
    }
    pbVar19 = pbVar19 - (int)(long)pbVar16;
    pbVar18 = (byte*)0x2;
    if ((1 << ((uint)(long)pbVar21 & 0x1f) & puVar20[(int)(long)pbVar21 >> 5]) != 0) {
      uVar22 = uVar22 | 2;
    }
    FUN_0008729e(iVar7, (int)(long)pbVar16);
    pbVar16 = (byte*)(long)param_3[1];
  } else {
    pbVar18 = (byte*)0x1;
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
    pbVar18 = (byte*)((uintptr_t)pbVar18 | 0x10);
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
      goto LAB_00078258;
    }
    FUN_00086c04(iVar8 + 0xc, iVar7 + 0xc, (*(volatile int*)(iVar7 + 0x10) + 2) * 4);
    FUN_00078654(param_1, iVar7);
  }
  iVar6 = *(volatile int*)(iVar8 + 0x10);
  *(volatile int*)(iVar8 + 0x10) = iVar6 + 1;
  *(volatile int*)(iVar8 + iVar6 * 4 + 0x14) = 1;
LAB_000784b0:
  if (pbVar18 == (byte*)0x2) {
    uVar22 = 2;
    if (((byte*)(long)(*param_3 - 1) != pbVar19) ||
        ((1 << ((uint)(long)pbVar19 & 0x1f) & *(volatile uint*)(iVar8 + 0x14 + ((int)(long)pbVar19 >> 5) * 4)) == 0))
      goto LAB_000784d6;
  } else if ((iVar17 < *(volatile int*)(iVar8 + 0x10)) ||
             ((((uint)(long)pbVar19 & 0x1f) != 0 &&
               (iVar6 = FUN_00087510(*(volatile int*)(iVar8 + 0x14 + iVar17 * 4 - 4)),
                iVar6 < (int)(0x20 - ((uint)(long)pbVar19 & 0x1f)))))) {
    FUN_0008729e(iVar8, 1);
    pbVar16 = pbVar16 + 1;
    if (param_3[2] < (int)(long)pbVar16) {
LAB_000782f2:
      FUN_00078654(param_1, iVar8);
      *param_5 = 0;
      return (byte*)0xa3;
    }
  }
  uVar22 = 1;
LAB_000784d6:
  pbVar18 = (byte*)(uintptr_t)(uVar22 | 0x20);
LAB_000784da:
  *param_5 = iVar8;
  *param_4 = (int)(long)pbVar16;
  return pbVar18;
}

