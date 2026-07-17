#include "g1_net_symbols.h"
/* net-core FUN_0101a38c @ 0x101a38c; full CFG extent 1940 bytes */
#include <stdint.h>
typedef uint8_t byte; typedef union { uint64_t all; struct { uint32_t _0_4_, _4_4_; }; } u64parts;
#define CARRY4(a,b) ((uint32_t)(a) > UINT32_MAX - (uint32_t)(b))
#define CONCAT44(hi,lo) ((((uint64_t)(uint32_t)(hi))<<32)|(uint32_t)(lo))
extern int FUN_01019204(); extern int64_t thunk_FUN_01025034(); extern int FUN_0101a130();
extern int FUN_0101a0e8(int,...); extern int FUN_010209f0(void); extern int FUN_01022f3c(void *,...);
extern int FUN_0100d4d0(void *,...); extern int FUN_0100f69c(int,...); extern int FUN_01008d00(int,...);
extern void FUN_0101deac(void); extern uint32_t *FUN_0101dda8(void); extern void FUN_0101dd48(uintptr_t,...);
extern uint32_t *FUN_0101ddc0(uint32_t,...); extern int FUN_0101dec4(void); extern uint32_t FUN_0101de10(uint32_t,...); extern void FUN_0101deb8(void);

int FUN_0101a38c(uint8_t *param_1,int param_2,int param_3,uint32_t param_4)

{
  int8_t cVar1;
  int64_t lVar2;
  int16_t sVar3;
  int bVar4;
  uint64_t uVar5;
  uint8_t *pcVar6;
  uint16_t uVar7;
  int iVar8;
  uint32_t uVar9;
  int iVar10;
  int iVar11;
  uint32_t *puVar12;
  int iVar13;
  int iVar14;
  uint32_t uVar15;
  uint32_t *puVar16;
  uint32_t uVar17;
  uint32_t uVar18;
  uint32_t uVar19;
  uint32_t uVar20;
  int iVar21;
  uint32_t uVar22;
  uint8_t uVar23;
  uint32_t uVar24;
  uint32_t uVar25;
  uint32_t uVar26;
  uint32_t uVar27;
  int64_t lVar28;
  int local_54;
  volatile int local_50;
  uint8_t local_40 [4];
  uint32_t local_3c;
  uint16_t local_38;
  uint8_t local_36;
  uint8_t local_35;
  u64parts local_30;

  pcVar6 = ((uint8_t *)((unsigned long)&g_net_session_state_block) /*=0x210010a0*/);
  iVar8 = FUN_01019204();
  lVar28 = thunk_FUN_01025034();
  uVar5 = (uint64_t)lVar28 >> 0x20;
  uVar9 = (uint32_t)lVar28;
  uVar25 = *(uint32_t *)(pcVar6 + 8);
  iVar10 = FUN_0101a130();
  uVar18 = 0;
  uVar24 = 0;
  uVar20 = 0;
  do {
    uVar18 = uVar18 + 1;
    uVar24 = uVar24 + *(int *)(pcVar6 + (uVar20 + 2) * 4) + iVar10;
    uVar20 = uVar18 & 0xff;
  } while (uVar20 <= (byte)pcVar6[0x2f]);
  uVar18 = *(uint32_t *)(pcVar6 + 4);
  if ((uVar18 == uVar24) && (param_3 != 0)) {
    if ((*pcVar6 == '\0') || (*(int16_t *)(pcVar6 + 0x74) == 0)) {
      if (param_2 != 0) {
        local_50 = 0;
        bVar4 = 1;
        goto LAB_0101a514;
      }
      cVar1 = *(char *)((uint32_t)(byte)pcVar6[0x2e] + iVar8 + 5);
      if (cVar1 == '\b') {
        iVar10 = 0x690;
      }
      else if (cVar1 == '\x04') {
        iVar10 = 0x140;
LAB_0101aa3e:
        iVar10 = iVar10 + 0x17e;
      }
      else {
        if (cVar1 == '\x02') {
          iVar10 = 0x48;
        }
        else {
          switch(cVar1) {
          case '\x01':
            iVar10 = 0x150;
            break;
          default:
            goto switchD_0101a5bc_caseD_2;
          case '\x04':
          case '\b':
            iVar10 = 0xa0;
            if (cVar1 == '\x04') goto LAB_0101aa3e;
          }
          if (cVar1 != '\x02') {
            iVar10 = iVar10 + 0x28;
            goto LAB_0101a754;
          }
        }
        iVar10 = iVar10 + 0x18;
      }
LAB_0101a754:
      iVar13 = FUN_010209f0();
      if (*(int *)(pcVar6 + 0x34) == 0x7fffffff && *(int *)(pcVar6 + 0x30) == -1) {
        uVar26 = 0;
        uVar27 = 0;
        local_50 = 0;
        bVar4 = 1;
        local_30.all = CONCAT44(local_30._4_4_,local_30._0_4_);
      }
      else {
        local_40[0] = 0;
        lVar2 = (uint64_t)0x10624dd3u * (uint64_t)(iVar13 + 0xa3a1);
        uVar20 = iVar10 + 0x11a + (uint32_t)((uint64_t)lVar2 >> 0x26);
        local_3c = uVar20;
        local_38 = FUN_0101a0e8(iVar13,*(int *)(pcVar6 + 0x30),(int)lVar2);
        local_35 = 1;
        iVar10 = FUN_0101a0e8(0);
        local_30.all = lVar28 + (uint64_t)(iVar10 + 0x135U & 0xffff);
        local_36 = 2;
        iVar10 = FUN_01022f3c(local_40);
        if (iVar10 == 0) {
                    /* WARNING: Subroutine does not return */
          do { FUN_01008d00(0x21,0x537); } while (1);
        }
        if ((int)(((*(int *)(pcVar6 + 0x34) - local_30._4_4_) -
                  (uint32_t)(*(uint32_t *)(pcVar6 + 0x30) < local_30._0_4_)) -
                 (uint32_t)(*(uint32_t *)(pcVar6 + 0x30) - local_30._0_4_ < uVar20)) < 0) {
          uVar26 = 0;
          local_50 = 0;
          bVar4 = 1;
          uVar25 = 0;
          uVar27 = uVar26;
        }
        else {
          uVar26 = 0;
          local_50 = 0;
          bVar4 = 1;
          uVar27 = 0;
        }
      }
      goto LAB_0101a59e;
    }
    if (param_2 != 0) goto LAB_0101a50e;
LAB_0101a5d0:
    uVar20 = *(uint32_t *)(pcVar6 + 0x50);
    iVar13 = *(int *)(pcVar6 + 0x54);
    uVar27 = 0;
    uVar19 = uVar18 * ((uVar9 - uVar20) / uVar18);
    uVar17 = uVar19 + uVar18 + uVar20;
    iVar10 = FUN_0101a0e8(0);
    if ((iVar10 + 0x135U & 0xffff) <= uVar17 - uVar9) {
      local_3c = *(uint32_t *)(pcVar6 + 0x3c);
      local_40[0] = 0;
      local_38 = FUN_0101a0e8(0);
      uVar17 = *(uint32_t *)(pcVar6 + 0x50);
      uVar20 = *(uint32_t *)(pcVar6 + 4);
      uVar19 = uVar20 * ((*(int *)(pcVar6 + 0x20) - uVar17) / uVar20);
      local_30._0_4_ = uVar19 + uVar17;
      local_30._4_4_ = *(int *)(pcVar6 + 0x54) + (uint32_t)CARRY4(uVar19,uVar17);
      local_36 = 1;
      local_35 = 1;
      if (*pcVar6 == '\x04') {
        if (uVar19 < uVar20 * 10) {
          local_36 = 2;
        }
        else {
          local_36 = 1;
        }
      }
      uVar27 = 0;
      uVar26 = FUN_0100d4d0(local_40);
      lVar28 = CONCAT44(local_30._4_4_,local_30._0_4_);
      bVar4 = 0;
      local_50 = 1;
      local_30.all = lVar28;
      goto LAB_0101a59e;
    }
    uVar22 = *(uint32_t *)(pcVar6 + 4);
    bVar4 = 0;
    cVar1 = *(char *)(iVar8 + 5);
    uVar26 = (uVar17 - (uVar22 * ((uint32_t)(*(int *)(pcVar6 + 0x20) - *(int *)(pcVar6 + 0x50)) / uVar22
                                 ) + *(int *)(pcVar6 + 0x50))) / uVar22;
    lVar28 = CONCAT44(iVar13 + (uint32_t)CARRY4(uVar18,uVar20) + (uint32_t)CARRY4(uVar19,uVar18 + uVar20) +
                      (uint32_t)CARRY4(uVar22,uVar17),uVar22 + uVar17);
    local_50 = 1;
  }
  else {
    if (param_2 == 0) {
      if (param_3 != 0) goto LAB_0101a5d0;
      uVar20 = *(uint32_t *)(pcVar6 + 0x50);
      iVar21 = *(int *)(pcVar6 + 0x54);
      uVar19 = uVar18 * ((uVar9 - uVar20) / uVar18);
      uVar17 = uVar19 + uVar20;
      iVar10 = FUN_01019204();
      iVar13 = FUN_0101a0e8(0);
      iVar11 = FUN_0101a130();
      cVar1 = pcVar6[0x2f];
      uVar26 = (uVar9 - uVar17) + (iVar13 + 0x135U & 0xffff);
      uVar25 = uVar26;
      if (*(uint32_t *)(pcVar6 + 4) <= uVar26) {
        uVar25 = uVar26 - *(uint32_t *)(pcVar6 + 4);
      }
      if (cVar1 == '\0') {
        uVar27 = 0;
      }
      else {
        uVar27 = *(int *)(pcVar6 + 8) + iVar11;
        uVar22 = uVar25;
        if (uVar27 <= uVar25) {
          uVar22 = uVar25 - uVar27;
        }
        uVar27 = (uint32_t)(uVar27 <= uVar25);
        uVar25 = uVar22;
        if (cVar1 != '\x01') {
          if ((uint32_t)(*(int *)(pcVar6 + 0xc) + iVar11) <= uVar22) {
            uVar27 = uVar27 + 1;
            uVar25 = uVar22 - (*(int *)(pcVar6 + 0xc) + iVar11);
          }
          if ((cVar1 != '\x02') && ((uint32_t)(*(int *)(pcVar6 + 0x10) + iVar11) <= uVar25)) {
            uVar27 = uVar27 + 1;
            uVar25 = uVar25 - (*(int *)(pcVar6 + 0x10) + iVar11);
          }
        }
      }
      iVar13 = uVar27 + 2;
      cVar1 = *(char *)(iVar10 + uVar27 + 5);
      uVar22 = *(uint32_t *)(pcVar6 + iVar13 * 4);
      if (cVar1 == '\b') {
        iVar10 = 0x690;
      }
      else if (cVar1 == '\x04') {
        iVar14 = 0x140;
LAB_0101aa14:
        iVar10 = iVar14 + 0x17e;
      }
      else {
        if (cVar1 == '\x02') {
          iVar10 = 0x48;
        }
        else {
          switch(cVar1) {
          case '\x01':
            iVar10 = 0x150;
            break;
          default:
            goto switchD_0101a5bc_caseD_2;
          case '\x04':
          case '\b':
            iVar14 = 0xa0;
            iVar10 = 0xa0;
            if (cVar1 == '\x04') goto LAB_0101aa14;
          }
          if (cVar1 != '\x02') {
            iVar10 = iVar10 + 0x28;
            goto LAB_0101a8e8;
          }
        }
        iVar10 = iVar10 + 0x18;
      }
LAB_0101a8e8:
      iVar14 = FUN_010209f0();
      if (uVar22 < iVar10 + uVar25 + 0x11a +
                   (uint32_t)((uint64_t)0x10624dd3u * (uint64_t)(iVar14 + 0xa3a1) >> 0x26)) {
        if (uVar27 < (byte)pcVar6[0x2f]) {
          if (*(uint32_t *)(pcVar6 + 4) <= uVar26) {
                    /* WARNING: Subroutine does not return */
            do { FUN_01008d00(0x21,0x4d7); } while (1);
          }
          uVar25 = *(uint32_t *)(pcVar6 + (uVar27 + 3) * 4);
          uVar22 = iVar11 + uVar25;
          uVar27 = uVar27 + 1;
        }
        else {
          uVar22 = *(uint32_t *)(pcVar6 + 4);
          if (uVar26 < uVar22) {
            uVar25 = *(uint32_t *)(pcVar6 + iVar13 * 4);
          }
          else {
            uVar25 = uVar22 << 1;
            uVar22 = uVar22 << 1;
            if (uVar25 <= uVar26) {
                    /* WARNING: Subroutine does not return */
              do { FUN_01008d00(0x21,0x4f4); } while (1);
            }
            uVar25 = *(uint32_t *)(pcVar6 + iVar13 * 4);
          }
        }
      }
      else {
        uVar25 = *(int *)(pcVar6 + iVar13 * 4) - uVar25;
        uVar22 = uVar26;
      }
      if ((int)uVar25 < 0) {
                    /* WARNING: Subroutine does not return */
        do { FUN_01008d00(0x21,0x4fd); } while (1);
      }
      uVar15 = *(uint32_t *)(pcVar6 + 0x50);
      uVar26 = *(uint32_t *)(pcVar6 + 4);
      lVar28 = CONCAT44(iVar21 + (uint32_t)CARRY4(uVar19,uVar20) + (uint32_t)CARRY4(uVar22,uVar17),
                        uVar22 + uVar17);
      uVar20 = uVar26 * ((*(int *)(pcVar6 + 0x18) - uVar15) / uVar26);
      iVar10 = uVar20 + uVar15;
      *(int *)(pcVar6 + 0x50) = iVar10;
      uVar26 = ((uVar22 + uVar17) - iVar10) / uVar26;
      *(uint32_t *)(pcVar6 + 0x54) = *(int *)(pcVar6 + 0x54) + (uint32_t)CARRY4(uVar20,uVar15);
      local_50 = 1;
      bVar4 = 0;
    }
    else {
LAB_0101a50e:
      bVar4 = 0;
      local_50 = param_2;
LAB_0101a514:
      lVar28 = lVar28 + 2000;
      FUN_0101deac();
      puVar12 = (uint32_t *)FUN_0101dda8();
      if (*pcVar6 == '\x05') {
        puVar16 = (uint32_t *)FUN_0101ddc0(*(uint32_t *)(*(int *)(pcVar6 + 0x28) + 0x2e0),0);
        if (puVar12 == puVar16) {
          local_54 = *(int *)(pcVar6 + 0x28);
          uVar20 = *(uint32_t *)(pcVar6 + 0x58);
          if (*(uint32_t *)(pcVar6 + 0x58) < *(uint32_t *)(local_54 + 0x2e0)) {
            uVar20 = *(uint32_t *)(local_54 + 0x2e0);
          }
          *(uint32_t *)(pcVar6 + 0x58) = uVar20;
          *(int *)(pcVar6 + 0x70) = local_54 + 0x2d8;
        }
        else {
          FUN_0101dd48(*(int *)(pcVar6 + 0x28) + 0x2d8);
          pcVar6[0x70] = '\0';
          pcVar6[0x71] = '\0';
          pcVar6[0x72] = '\0';
          pcVar6[0x73] = '\0';
          local_54 = *(int *)(pcVar6 + 0x28);
          if (local_54 == 0) {
                    /* WARNING: Subroutine does not return */
            do { FUN_01008d00(0x21,0x7a2); } while (1);
          }
        }
        if (puVar16 == (uint32_t *)0x0) {
          *(uint32_t *)(local_54 + 0x2d8) = 0;
          *(uint32_t *)(local_54 + 0x2dc) = 0;
        }
        else {
          iVar10 = FUN_0101dec4();
          if (iVar10 == 0) {
                    /* WARNING: Subroutine does not return */
            do { FUN_01008d00(0x21,0x7a8); } while (1);
          }
          uVar20 = puVar16[2];
          uVar17 = *puVar16;
          uVar19 = puVar16[1];
          *(uint32_t *)(local_54 + 0x2d8) = uVar17 + uVar20;
          *(uint32_t *)(local_54 + 0x2dc) = uVar19 + CARRY4(uVar17,uVar20);
          *(int16_t *)(local_54 + 0x2fc) = (short)puVar16[9];
        }
      }
      FUN_0101dd48(((unsigned long)&g_net_session_queue_obj) /*=0x210010f0*/,puVar12);
      if (puVar12 != (uint32_t *)0x0) {
        uVar26 = *puVar12;
        uVar19 = puVar12[2];
        uVar17 = puVar12[1];
        uVar20 = puVar12[9];
        uVar27 = *(uint32_t *)(pcVar6 + 4);
        *(int16_t *)(pcVar6 + 0x74) = (short)uVar20;
        uVar20 = FUN_0101de10(uVar19 + uVar26,uVar17 + CARRY4(uVar19,uVar26),uVar27,
                              (int)(short)uVar20,lVar28);
        if (uVar27 < uVar20) {
                    /* WARNING: Subroutine does not return */
          do { FUN_01008d00(0x21,0x3fc); } while (1);
        }
        lVar28 = lVar28 + (uint64_t)uVar20;
      }
      FUN_0101deb8();
      *(uint32_t *)(pcVar6 + 0x50) = (uint32_t)lVar28 - *(uint32_t *)(pcVar6 + 4);
      *(uint32_t *)(pcVar6 + 0x54) =
           (int)((uint64_t)lVar28 >> 0x20) - (uint32_t)((uint32_t)lVar28 < *(uint32_t *)(pcVar6 + 4));
      if (param_4 == 0) {
        uVar26 = 1;
        pcVar6[0x30] = -1;
        pcVar6[0x31] = -1;
        pcVar6[0x32] = -1;
        pcVar6[0x33] = -1;
        pcVar6[0x34] = -1;
        pcVar6[0x35] = -1;
        pcVar6[0x36] = -1;
        pcVar6[0x37] = '\x7f';
        uVar27 = 0;
        local_30.all = CONCAT44(local_30._4_4_,local_30._0_4_);
      }
      else {
        uVar27 = 0;
        *(uint64_t *)(pcVar6 + 0x30) = (uint64_t)param_4 * 10000 + lVar28;
        uVar26 = 1;
        local_30.all = CONCAT44(local_30._4_4_,local_30._0_4_);
      }
    }
LAB_0101a59e:
    cVar1 = *(char *)(iVar8 + uVar27 + 5);
  }
  if (cVar1 == '\b') {
    iVar8 = 0x690;
  }
  else if (cVar1 == '\x04') {
    iVar8 = 0x2be;
  }
  else {
    if (cVar1 == '\x02') {
      iVar8 = 0x48;
    }
    else {
      if (cVar1 == '\x01') {
        iVar8 = 0x150;
      } else if ((cVar1 == '\x04') || (cVar1 == '\b')) {
        iVar8 = 0xa0;
      } else {
switchD_0101a5bc_caseD_2:
        cVar1 = (int8_t)FUN_01008d00(5,0x104);
        if (cVar1 == '\x04') {
          iVar8 = 0x140 + 0x17e;
          goto LAB_0101a666;
        }
        if (cVar1 == '\x02') {
          iVar8 = 0x48 + 0x18;
          goto LAB_0101a666;
        }
        /* Returning through the firmware's noreturn panic island physically
           enters its final timing-maintenance loop. */
        (void)FUN_010209f0();
        *(volatile uint32_t *)(pcVar6 + 0x50) = 0;
        *(volatile uint32_t *)(pcVar6 + 0x54) = 0;
        for (;;) {
          (void)FUN_010209f0();
          (void)FUN_0101a0e8(0);
          *(volatile uint32_t *)(pcVar6 + 0x50) = 0;
          *(volatile uint32_t *)(pcVar6 + 0x54) = 0;
        }
      }
      if (cVar1 != '\x02') {
        iVar8 = iVar8 + 0x28;
        goto LAB_0101a666;
      }
    }
    iVar8 = iVar8 + 0x18;
  }
LAB_0101a666:
  iVar10 = FUN_010209f0();
  uVar19 = iVar8 + 0x11a + (uint32_t)((uint64_t)0x10624dd3u * (uint64_t)(iVar10 + 0xa3a1) >> 0x26);
  uVar20 = *(uint32_t *)(pcVar6 + 0x30) - (uint32_t)lVar28;
  iVar8 = (*(int *)(pcVar6 + 0x34) - (int)((uint64_t)lVar28 >> 0x20)) -
          (uint32_t)(*(uint32_t *)(pcVar6 + 0x30) < (uint32_t)lVar28);
  if (iVar8 < (int)(uint32_t)(uVar20 == 0)) {
    uVar25 = 0;
  }
  else if ((int)(uint32_t)(uVar25 < uVar20) <= -iVar8) {
    uVar25 = uVar20;
  }
  if (*(uint32_t *)(pcVar6 + (uVar27 + 2) * 4) <= uVar25) {
    uVar25 = *(uint32_t *)(pcVar6 + (uVar27 + 2) * 4);
  }
  *(uint32_t *)(pcVar6 + 0x3c) = uVar25;
  if ((uVar26 != 0) && (local_50 != 0)) {
    uVar25 = FUN_0100f69c((int)*(int16_t *)(pcVar6 + 0x74),(uVar26 & 0x7fff) << 1);
    iVar8 = *(int *)(pcVar6 + 0x28);
    sVar3 = *(int16_t *)(pcVar6 + 0x74) - (short)uVar25;
    *(int16_t *)(pcVar6 + 0x74) = sVar3;
    if (iVar8 != 0) {
      *(int16_t *)(iVar8 + 0x2fc) = sVar3;
      uVar20 = *(uint32_t *)(iVar8 + 0x2d8);
      *(uint32_t *)(iVar8 + 0x2d8) = uVar20 + uVar25;
      *(uint32_t *)(iVar8 + 0x2dc) =
           *(int *)(iVar8 + 0x2dc) + ((int)uVar25 >> 0x1f) + (uint32_t)CARRY4(uVar20,uVar25);
    }
    uVar20 = *(uint32_t *)(pcVar6 + 0x50);
    lVar28 = lVar28 + (int)uVar25;
    *(uint32_t *)(pcVar6 + 0x50) = uVar20 + uVar25;
    *(uint32_t *)(pcVar6 + 0x54) =
         ((int)uVar25 >> 0x1f) + *(int *)(pcVar6 + 0x54) + (uint32_t)CARRY4(uVar20,uVar25);
  }
  if (param_2 != 0) {
    *(int64_t *)(pcVar6 + 0x18) = lVar28;
  }
  uVar23 = 1;
  uVar25 = uVar19;
  if (uVar18 != uVar24) {
    uVar25 = *(uint32_t *)(pcVar6 + 0x3c);
  }
  *(int64_t *)(pcVar6 + 0x20) = lVar28;
  *(uint32_t *)(pcVar6 + 0x38) = uVar25;
  param_1[0xb] = 1;
  uVar7 = FUN_0101a0e8(0);
  cVar1 = *pcVar6;
  *(uint16_t *)(param_1 + 8) = uVar7;
  if ((cVar1 == '\x04') &&
     ((uint32_t)((int)lVar28 - *(int *)(pcVar6 + 0x50)) < (uint32_t)(*(int *)(pcVar6 + 4) * 10))) {
    uVar23 = 2;
  }
  param_1[10] = uVar23;
  *(uint32_t *)(param_1 + 4) = *(uint32_t *)(pcVar6 + 0x38);
  if (bVar4) {
    *param_1 = 1;
    uVar25 = *(uint32_t *)(pcVar6 + 0x30) - uVar9;
    iVar8 = (*(int *)(pcVar6 + 0x34) - (int)uVar5) - (uint32_t)(*(uint32_t *)(pcVar6 + 0x30) < uVar9);
    if (iVar8 < (int)(uint32_t)(uVar25 == 0)) {
      uVar25 = 0;
    }
    else if (-iVar8 < (int)(uint32_t)(0x0f424000u < uVar25)) {
      uVar25 = 0x0f424000u;
    }
    *(uint32_t *)(param_1 + 0x10) = uVar25 - uVar19;
  }
  else {
    *param_1 = 0;
    *(int64_t *)(param_1 + 0x10) = lVar28;
  }
  return uVar19 <= *(uint32_t *)(pcVar6 + 0x3c);
}
