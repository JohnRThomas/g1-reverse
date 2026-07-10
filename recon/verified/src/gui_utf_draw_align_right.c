/* Reconstructed gui_utf_draw_align_right @ 0x44ec4  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;

extern void DEBUG_PRINT(u32,u32,u32,u32);
extern u32 FUN_000167a8(void);
extern void FUN_00019c70(void);
extern u32 FUN_000431a8(void);
extern u32 FUN_00043e58(u32,u32);
extern i32 FUN_0004588c(u32,u32,void*,void*,void*,u32);
extern void FUN_000471cc(u32,u32,u32,u32,u32,u32);
extern void FUN_00047260(u32,u32,u32,u32,u32,u32);
extern u16* FUN_000478d8(u32,void*);
extern void FUN_0007d53a(u32,void*,u32,u32,u32,u32);
extern u32 FUN_0007d860(u32);
extern void FUN_00086c1e(void*,u32,u32,u32);

typedef u32 (*fnptr_t)(u32,u32,u32,u32,u32);

u32 gui_utf_draw_align_right(u32 param_1, u32 param_2, i32 param_3, u32 param_4, i32 param_5,
                              i32 param_6, i32 param_7, u32 param_8, u32 param_9, i32 param_10,
                              fnptr_t param_11, i32 param_12)
{
  i32 iVar1;
  u16 *puVar2;
  i32 iVar3, iVar4, iVar5;
  int bVar6;
  u8 *pbVar7;
  u32 uVar8;
  u32 uVar9;
  u32 uVar10, uVar11;
  i32 iVar12;
  u16 *puVar13;
  u32 uVar14, uVar15;
  u32 local_2f8;
  u32 local_2f4;
  u32 local_2ec;
  u32 local_2e8;
  u16 local_2da;
  u32 local_2d8;
  i32 local_2d4;
  i32 local_2d0;
  u8 local_2cc[680];

  (void)param_1;

  local_2da = 0;
  local_2d8 = 0;
  puVar2 = FUN_000478d8(param_2, &local_2da);
  local_2d4 = 0;
  local_2d0 = 0;

  if (param_10 == 0) {
    if (param_11 != 0) goto LAB_000451a2;
    if (param_12 == 0) {
      iVar3 = FUN_000431a8();
      if ((i32)(iVar3 << 30) < 0) {
        FUN_000471cc(*(volatile u32*)0x2000a034UL, 0, param_4, param_5, param_6, param_7);
      }
      uVar10 = 0;
      bVar6 = 1;
      uVar8 = 0;
      local_2f4 = 0;
      local_2f8 = 0;
      local_2e8 = param_4;
      for (local_2ec = 0; (i32)local_2ec < (i32)(u32)local_2da; local_2ec = local_2ec + 1) {
        if (bVar6) {
          uVar11 = 0;
          uVar14 = local_2ec;
          for (puVar13 = puVar2;
               ((i32)uVar14 < (i32)(u32)local_2da) && (uVar15 = (u32)*puVar13, uVar15 != 0xd) &&
               (uVar15 != 10);
               puVar13 = puVar13 + 1) {
            iVar3 = FUN_0007d860(uVar15);
            if (iVar3 == 0) {
              iVar3 = FUN_0004588c(param_3, uVar15, &local_2d4, &local_2d0, &local_2d8, 0);
              if (iVar3 < 0) {
                if (1 < *(volatile i32*)0x2000230cUL) {
                  if (*(volatile i32*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x000aaa58UL, 0x000aad4bUL, uVar15, 0);
                  } else {
                    FUN_00019c70();
                  }
                }
              } else {
                uVar11 = uVar11 + (u32)local_2d4;
                iVar3 = FUN_00043e58(*puVar13, puVar13[1]);
                uVar11 = ((uVar11 & 0xffff) + (u32)iVar3) & 0xffff;
              }
            }
            uVar14 = uVar14 + 1;
          }
          local_2e8 = param_4;
          if (uVar11 <= (u32)(param_6 - (i32)param_4)) {
            local_2e8 = (u32)(param_6 - (i32)uVar11);
          }
          local_2e8 = local_2e8 & 0xfffffffeUL;
        }
        puVar13 = puVar2 + 1;
        uVar14 = (u32)*puVar2;
        iVar3 = FUN_0007d860(uVar14);
        if (iVar3 == 0) {
          iVar4 = FUN_0004588c(param_3, uVar14, &local_2d4, &local_2d0, &local_2d8, 0);
          iVar1 = local_2d0;
          iVar3 = local_2d4;
          if (iVar4 < 0) {
            if (1 < *(volatile i32*)0x2000230cUL) {
              if (*(volatile i32*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000aaa58UL, 0x000aad4bUL, uVar14, 0);
              } else {
                FUN_00019c70();
              }
            }
          } else {
            iVar4 = local_2d4 / 2;
            iVar5 = local_2d0 * iVar4;
            FUN_00086c1e(local_2cc, local_2d8, iVar5, 0x2a4);
            if (local_2ec < param_9) {
              pbVar7 = local_2cc;
              for (iVar12 = 0; iVar12 < iVar5; iVar12 = iVar12 + 1) {
                *pbVar7 = *pbVar7 & *(volatile u8*)0x200034f6UL;
                pbVar7 = pbVar7 + 1;
              }
            }
            iVar5 = FUN_00043e58(*puVar2, *puVar13);
            local_2f4 = local_2f4 + (u32)iVar5 + (u32)iVar3;
            if ((u32)(param_6 - (i32)param_4) < local_2f4) {
              uVar8 = uVar8 + (u32)iVar1;
              if (param_3 == 0) {
                uVar8 = uVar8 + 1;
              }
              uVar10 = uVar10 + 1;
              if ((param_8 <= uVar10) || ((u32)(param_7 - param_5) <= uVar8)) break;
              FUN_0007d53a(*(volatile u32*)0x2000a034UL, local_2cc, iVar4, iVar1, local_2e8, uVar8 + param_5);
              iVar3 = FUN_00043e58(*puVar2, *puVar13);
              local_2f8 = (u32)iVar3 + (u32)local_2d4;
              local_2f4 = local_2f8;
            } else {
              FUN_0007d53a(*(volatile u32*)0x2000a034UL, local_2cc, iVar4, iVar1, local_2e8 + local_2f8, uVar8 + param_5);
              iVar3 = FUN_00043e58(*puVar2, *puVar13);
              local_2f8 = local_2f8 + (u32)iVar3 + (u32)local_2d4;
            }
          }
LAB_0004502c:
          bVar6 = 0;
        } else {
          if ((iVar3 != -1) || ((uVar14 != 0xd) && (uVar14 != 10))) goto LAB_0004502c;
          if (local_2d0 == 0) {
            if (param_3 == 0) {
              uVar8 = uVar8 + 0x1b;
            } else {
              uVar8 = uVar8 + 0x1a;
            }
          } else {
            uVar8 = uVar8 + (u32)local_2d0;
            if (param_3 == 0) {
              uVar8 = uVar8 + 1;
            }
          }
          uVar10 = uVar10 + 1;
          if ((param_8 <= uVar10) || ((u32)(param_7 - param_5) <= uVar8)) break;
          bVar6 = 1;
          local_2f8 = 0;
          local_2f4 = 0;
        }
        puVar2 = puVar13;
      }
      iVar3 = FUN_000431a8();
      if ((i32)(iVar3 << 30) < 0) {
        iVar3 = FUN_000167a8();
        uVar9 = *(volatile u32*)(iVar3 + 0xeb4);
        iVar3 = FUN_000167a8();
        FUN_00047260(uVar9, *(volatile u32*)(iVar3 + 0xeb8), param_4, param_5, param_6, param_7);
      }
    }
  } else if (param_11 != 0) {
    goto LAB_000451a2;
  }
  return 0;

LAB_000451a2:
  if (1 < *(volatile i32*)0x2000230cUL) {
    if (*(volatile i32*)0x20007554UL == 0) {
      DEBUG_PRINT(0x000aaa7fUL, 0x000aad4bUL, 0, 0);
    } else {
      FUN_00019c70();
    }
  }
  uVar9 = (*param_11)(0, param_2, param_3, param_4, param_5);
  return uVar9;
}

