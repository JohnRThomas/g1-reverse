#include "g1_net_symbols.h"
/* net-core FUN_01021ee0 @ 0x1021ee0  (parity 300 trials PROVEN) */
#include <stdint.h>
typedef uint8_t  byte;
typedef uint8_t  undefined1;
typedef uint16_t ushort;
typedef uint16_t undefined2;
typedef uint32_t uint;
typedef uint32_t undefined4;
typedef uint64_t undefined8;
typedef uint64_t ulonglong;
typedef int64_t  longlong;
#define CONCAT44(h,l) (((uint64_t)(uint32_t)(h)<<32)|(uint32_t)(l))

extern uint64_t FUN_01024440(int,...);
extern void     FUN_010244cc(int,int*,void*);
extern uint32_t FUN_01024644(void);
extern int      FUN_01024664(void);
extern int      FUN_010246d8(void);
extern void     FUN_010246e4(void);
extern void     FUN_01024778(void);
extern uint32_t FUN_01024ad0(void);
extern void     FUN_01024c6c(uint,uint);
extern int64_t  FUN_0102501c(void);
extern uint64_t FUN_01025084(void);
extern uint64_t FUN_010250d0(int,int,int,int,int);
extern void     FUN_0102524c(int);
extern void     FUN_010256dc(int,int,...);

undefined4 FUN_01021ee0(uint param_1,int param_2,int param_3,int param_4)
{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  longlong lVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 extraout_r1;
  undefined4 uVar10;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  int iVar22;
  int bVar23;
  longlong lVar24;
  undefined8 uVar25;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  byte local_9c;
  int local_98;
  uint local_90;
  int local_8c;
  uint local_84;
  uint local_80;
  undefined1 uStack_5d;
  int local_5c[2];
  undefined4 uStack_54;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 local_30[4];
  undefined4 uStack_2c;

  iVar5 = ((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/;
  lVar24 = FUN_0102501c();
  uVar11 = (uint)((ulonglong)lVar24 >> 0x20);
  uVar16 = (uint)lVar24;
  local_84 = FUN_01024644();
  iVar22 = iVar5 + param_4 * 0x20;
  **(undefined4 **)(iVar5 + 0x4d4) = 1;
  iVar17 = param_4 * 0x20 + 8;
  iVar13 = iVar5 + 0xd0 + iVar17;
  uVar18 = *(uint *)(iVar5 + 0xd0 + iVar17);
  bVar1 = *(byte *)(iVar13 + 0xc);
  local_a8 = *(uint *)(iVar13 + 4);
  uVar3 = *(ushort *)(iVar13 + 0xe);
  uVar21 = (uint)uVar3;
  local_8c = *(int *)(iVar13 + 8);
  local_48 = *(undefined4 *)(iVar22 + 0xd8);
  local_44 = *(undefined4 *)(iVar22 + 0xdc);
  local_40 = *(undefined4 *)(iVar22 + 0xe0);
  local_3c = *(undefined4 *)(iVar22 + 0xe4);
  local_38 = *(undefined4 *)(iVar22 + 0xe8);
  uStack_34 = *(undefined4 *)(iVar22 + 0xec);
  uVar7 = FUN_01024440(uVar18 & 0xffffff);
  local_80 = uVar21 + 1 + (uint)bVar1 + uVar7;
  if (0x1e847fff < uVar7) goto LAB_01022550;
  if ((int)0x1e847fff < (int)local_80) {
    local_80 = local_80 + 0xe17b8000;
  }
  else if ((int)local_80 < 0) {
    local_80 = local_80 + 0x1e848000;
  }
  local_9c = *(byte *)(iVar5 + 0x28);
  uVar14 = (uint)local_9c;
  cVar2 = *(char *)(iVar5 + 0x29);
  uVar7 = FUN_01024ad0();
  if (uVar21 == 0) {
    iVar13 = FUN_010246d8();
    local_a4 = 0;
    uVar20 = 0;
    if (iVar13 == 0x356) goto LAB_01022168;
LAB_01021f96:
    if (iVar13 == 0x5f5) {
      uVar20 = 0x32;
      uVar19 = 0x35;
      uVar15 = 0x32;
      local_90 = 0x32;
      local_a0 = 0x35;
    }
    else if (iVar13 == 0x18c) {
      uVar20 = 0xd;
      uVar15 = 0xd;
      uVar19 = 0x10;
      local_90 = 0xd;
      local_a0 = 0x10;
    }
    else {
      uVar20 = 0;
      uVar19 = 3;
      uVar15 = 0;
      local_90 = 0;
      local_a0 = 3;
    }
    uVar8 = uVar15;
    uVar9 = uVar19;
    uVar12 = uVar20;
    if (uVar21 < local_84) goto LAB_01022180;
LAB_01021fc0:
    uVar15 = uVar8;
    uVar8 = 0;
    uVar19 = uVar9;
    uVar20 = uVar12;
  }
  else {
    uVar20 = uVar7;
    if ((*(uint *)(iVar5 + 0x44) & *(uint *)(iVar5 + 0x40)) != 0xffffffff) {
      uVar20 = uVar7 | 1;
    }
    local_a4 = (uVar20 ^ 1) & 0xff;
    iVar13 = FUN_010246d8();
    uVar20 = local_a4;
    if (iVar13 != 0x356) goto LAB_01021f96;
LAB_01022168:
    local_a4 = uVar20;
    uVar12 = 0x1c;
    uVar20 = 0x1c;
    uVar9 = 0x1f;
    uVar19 = 0x1f;
    uVar15 = 0x1c;
    local_90 = 0x1c;
    local_a0 = 0x1f;
    uVar8 = uVar20;
    if (local_84 <= uVar21) goto LAB_01021fc0;
LAB_01022180:
    iVar13 = local_80 - (local_84 + 1);
    if (0x1e847fff < local_80) {
LAB_01022550:
                    /* WARNING: Subroutine does not return (panic); the HW never
                       falls through - model the non-returning assert cluster as
                       an infinite call loop so the differential prefix matches. */
      FUN_010256dc(0x70,0x5a0);
      for (;;) { FUN_010256dc(0x70,0x5a0); }
    }
    if ((int)0x1e847fff < iVar13) {
      iVar13 = 0xe17b8000 + iVar13;
    }
    else if (iVar13 < 0) {
      iVar13 = 0x1e848000 + iVar13;
    }
    FUN_010244cc(iVar13,local_5c,&uStack_5d);
    uVar8 = uVar18 - local_5c[0] & 0xffffff;
  }
  if (local_a4 == 0) {
    if (uVar14 == 0) {
      uVar19 = 3;
      local_a0 = 3;
      uVar15 = uVar14;
      uVar20 = uVar14;
    }
    else {
      uVar19 = 5;
      local_a0 = 5;
      uVar15 = 2;
      uVar20 = 2;
    }
  }
  uVar12 = param_1;
  if (lVar24 != -1) {
    if (local_a8 < uVar11 || uVar11 - local_a8 < (uint)(uVar18 <= uVar16)) {
      lVar4 = lVar24 - CONCAT44(local_a8,uVar18);
      uVar11 = (uint)((ulonglong)lVar4 >> 0x20);
      bVar23 = 0x7fffff < (uint)lVar4;
      if (uVar11 != 0 || uVar11 < bVar23) {
                    /* WARNING: Subroutine does not return */
        FUN_010256dc(0x70,0xa08,uVar11 - !bVar23);
      }
      uVar9 = uVar18 - uVar16;
    }
    else {
      uVar9 = uVar18 - uVar16;
      uVar11 = (local_a8 - uVar11) - (uint)(uVar18 < uVar16);
      if (uVar11 != 0 || uVar11 < (0x7fffff < uVar9)) {
                    /* WARNING: Subroutine does not return */
        FUN_010256dc(0x70,0xa04,uVar11 - (0x7fffff >= uVar9));
      }
    }
    if ((((0 < (int)uVar9) && (uVar12 = uVar16, uVar19 = uVar20, local_a0 = uVar15, local_a4 != 0))
        && (*(char *)(iVar5 + 0x48) != '\0')) && (uVar19 = uVar14, local_a0 = uVar14, uVar14 != 0))
    {
      uVar19 = 2;
      local_a0 = uVar19;
    }
  }
  uVar20 = uVar18 - uVar8;
  uVar11 = local_a8 - (uVar18 < uVar8);
  uVar15 = uVar20 - 1;
  iVar13 = uVar15 - uVar12;
  local_98 = (uVar11 - 1) + (uint)(uVar20 != 0);
  if (iVar13 < (int)uVar19) {
    if ((uVar8 == 0) || ((cVar2 == '\0' && (iVar17 = FUN_01024664(), iVar17 != 0)))) {
      if (local_a4 != 0) {
        return 0;
      }
      if (uVar14 == 0) {
        return 0;
      }
      uVar19 = local_a0 - 2;
    }
    else {
      if ((local_a4 == 0) && (uVar14 != 0)) {
        uVar19 = local_a0 - 2;
      }
      uVar15 = uVar18 - 1;
      iVar13 = uVar15 - uVar12;
      local_98 = (local_a8 - 1) + (uint)(uVar18 != 0);
      local_84 = 0;
      uVar11 = local_a8;
      uVar20 = uVar18;
    }
    if (iVar13 < (int)uVar19) {
      return 0;
    }
    local_9c = 0;
  }
  else if (uVar8 != 0) {
    local_8c = local_8c + uVar8;
    uVar18 = uVar20;
    local_a8 = uVar11;
  }
  if (uVar7 == 0) {
    uVar7 = *(uint *)(iVar5 + 0x40);
    if (((*(int *)(iVar5 + 0x44) != -1 || uVar7 != 0xffffffff) &&
        (uVar11 = uVar11 - *(int *)(iVar5 + 0x44),
        uVar11 == uVar20 < uVar7 && (uint)(local_90 <= uVar20 - uVar7) <= uVar11 - (uVar20 < uVar7))
        ) && (uVar21 != 0)) {
      return 0;
    }
  }
  uVar7 = local_98 - param_2;
  uVar11 = (uint)(uVar15 < param_1);
  iVar13 = FUN_010246d8();
  if (iVar13 == 0x356) {
    uVar14 = 0x27;
LAB_0102209c:
    if (uVar7 == uVar11 && (uint)(uVar14 <= uVar15 - param_1) <= uVar7 - uVar11) goto LAB_010220a6;
LAB_010222dc:
    uVar7 = uVar21;
    if (uVar21 != 0) {
      uVar7 = 1;
    }
    FUN_01024c6c(uVar15,local_98);
LAB_010220d4:
    lVar24 = CONCAT44(local_98,uVar15);
    if (local_98 == -1 && uVar15 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_010256dc(0x70,0xa7a);
    }
  }
  else {
    if (iVar13 != 0x5f5) {
      if (iVar13 == 0x18c) {
        uVar14 = 0x18;
      }
      else {
        uVar14 = 0xb;
      }
      goto LAB_0102209c;
    }
    if (uVar7 != uVar11 || uVar7 - uVar11 < (uint)(0x3c < uVar15 - param_1)) goto LAB_010222dc;
LAB_010220a6:
    if (param_3 != 1) {
      local_a4 = local_a4 & 1;
      if (lVar24 == -1) {
        local_a4 = 1;
      }
      if (local_a4 == 0) {
        lVar4 = lVar24 - CONCAT44(local_98,uVar15);
        iVar13 = (int)((ulonglong)lVar4 >> 0x20);
        uVar7 = 0;
        if (iVar13 < (int)(uint)((uint)lVar4 < 5)) {
          if ((int)(uint)(uVar16 == uVar15) <= iVar13) {
            return 0;
          }
          goto LAB_010220e4;
        }
        FUN_01024c6c(uVar15,local_98);
      }
      else {
        uVar7 = 0;
        FUN_01024c6c(uVar15,local_98);
      }
      goto LAB_010220d4;
    }
    if (lVar24 == -1) {
                    /* WARNING: Subroutine does not return */
      FUN_010256dc(0x70,0x907);
    }
    uVar7 = 0;
  }
LAB_010220e4:
  local_98 = (int)((ulonglong)lVar24 >> 0x20);
  uVar11 = (uint)lVar24;
  uVar16 = (local_8c + uVar18) - (uVar11 & 0xffffff) & 0xffffff;
  if (uVar16 < 0x800001) {
    uVar16 = (uVar18 - (uVar11 & 0xffffff) & 0xffffff) - 1;
  }
  if (0x7fffff < uVar16) {
    return 0;
  }
  uVar25 = FUN_01024440(0);
  uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
  uVar16 = local_80 - (int)uVar25;
  if (uVar16 < 0x0f424000) {
LAB_01022328:
    if (*(char *)(iVar5 + 0x2a) == '\0') {
      uVar14 = local_84;
      if (local_84 < uVar21) {
        uVar14 = uVar21;
      }
      if ((int)uVar16 <= (int)(uVar14 + 0x1e)) {
LAB_010224de:
                    /* WARNING: Subroutine does not return */
        FUN_010256dc(0x70,0xa8e);
      }
    }
  }
  else {
    local_80 = (int)uVar25 - local_80;
    if (0x0f424000 <= local_80) {
      if (0x1e847fff < uVar16) {
        uVar16 = uVar16 + 512000000;
      }
      else {
        if (local_80 <= 0x1e847fff) {
                    /* WARNING: Subroutine does not return */
          FUN_010256dc(0x70,0xb76);
        }
        uVar16 = 0xe17b8000 - local_80;
      }
      goto LAB_01022328;
    }
    uVar16 = -local_80;
    if (*(char *)(iVar5 + 0x2a) == '\0') goto LAB_010224de;
  }
  if (param_3 != 1) {
    FUN_0102524c(2);
    FUN_0102524c(1);
    uVar10 = extraout_r1;
  }
  if (uVar21 < local_84) {
    uVar25 = FUN_010250d0(2,1,uVar16 - local_84,0,1);
    if (uVar21 != 0) {
      if ((int)uVar25 == 0) goto LAB_01022400;
      uVar25 = FUN_010250d0(1,1,uVar16 - uVar21,0,1);
    }
LAB_0102243e:
    if ((int)uVar25 == 0) {
LAB_01022400:
      FUN_0102524c(2);
      FUN_0102524c(1);
      return 0;
    }
    uVar25 = FUN_010250d0(0,(int)((ulonglong)uVar25 >> 0x20),uVar16,0,1);
    uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
    if ((int)uVar25 == 0) goto LAB_01022400;
    if (uVar21 == 0) goto LAB_01022372;
LAB_0102245a:
    if (uVar7 == 0) {
      if (*(int *)(iVar5 + 0x44) == -1 && *(int *)(iVar5 + 0x40) == -1) {
        FUN_010246e4();
        uVar25 = FUN_01025084();
        uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
        *(undefined8 *)(iVar5 + 0x40) = uVar25;
      }
LAB_0102246c:
      if (*(char *)(iVar5 + 0x48) != '\0') {
        FUN_0102524c(5);
        *(undefined1 *)(iVar5 + 0x48) = 0;
        uVar10 = extraout_r1_00;
      }
      goto LAB_01022392;
    }
    if (*(int *)(iVar5 + 0x44) != -1 || *(int *)(iVar5 + 0x40) != -1) {
      FUN_01024778();
      *(undefined4 *)(iVar5 + 0x40) = 0xffffffff;
      *(undefined4 *)(iVar5 + 0x44) = 0xffffffff;
    }
  }
  else {
    if (local_84 < uVar21) {
      uVar25 = FUN_010250d0(1,1,uVar16 - uVar21,0,1);
      if (local_84 != 0) {
        if ((int)uVar25 == 0) goto LAB_01022400;
        uVar25 = FUN_010250d0(2,1,uVar16 - local_84,0,1);
      }
      goto LAB_0102243e;
    }
    if (uVar21 != 0 || local_84 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_010256dc(0x70,0x9a3);
    }
    uVar25 = FUN_010250d0(0,uVar10,uVar16,0,1);
    uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
    if ((int)uVar25 == 0) goto LAB_01022400;
LAB_01022372:
    if (*(char *)(iVar5 + 0x48) != '\0') goto LAB_0102245a;
    if (*(int *)(iVar5 + 0x44) != -1 || *(int *)(iVar5 + 0x40) != -1) {
      FUN_01024778();
      *(undefined4 *)(iVar5 + 0x40) = 0xffffffff;
      *(undefined4 *)(iVar5 + 0x44) = 0xffffffff;
      uVar10 = extraout_r1_01;
      if (uVar7 != 0) goto LAB_010224a2;
      goto LAB_0102246c;
    }
    if (uVar7 == 0) goto LAB_01022392;
  }
LAB_010224a2:
  uVar25 = FUN_010250d0(5,0,uVar11 - local_90,local_98 - (uint)(uVar11 < local_90),0);
  uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
  if ((int)uVar25 == 0) {
                    /* WARNING: Subroutine does not return */
    FUN_010256dc(0x70,0x2fa);
  }
  if (*(char *)(iVar5 + 0x48) == '\0') {
    *(undefined1 *)(iVar5 + 0x48) = 1;
  }
LAB_01022392:
  if ((int)uVar16 <= (int)(uVar21 + 0x19)) {
                    /* WARNING: Subroutine does not return */
    FUN_010256dc(0x70,0xacc);
  }
  iVar13 = FUN_010250d0(3,uVar10,uVar16 - (uVar21 + 0x19),0,1);
  if (iVar13 != 0) {
    **(undefined4 **)(iVar5 + 0x4d4) = 0;
  }
  puVar6 = ((undefined4*)((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/);
  local_3c = ((uint)(ushort)uVar3 << 16) | (local_3c & 0xffff);
  local_30[1] = cVar2;
  local_30[0] = local_9c;
  local_3c = (local_3c & 0xffffff00) | (byte)bVar1;
  local_30[2] = 0;
  *((undefined4*)((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/) = 0;
  puVar6[1] = uStack_54;
  puVar6[2] = 0xffffffff;
  puVar6[3] = 0xffffffff;
  puVar6[4] = uVar18;
  puVar6[5] = local_a8;
  puVar6[6] = local_8c;
  puVar6[7] = local_3c;
  puVar6[8] = local_38;
  puVar6[9] = uStack_34;
  puVar6[10] = *(undefined4*)local_30;
  puVar6[0xb] = uStack_2c;
  return 1;
}
