/* Reconstructed gui_utf_draw_truncate @ 0x44818  (parity: 300/300 trials, PROVEN) */
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

u32 gui_utf_draw_truncate(u32 param_1, u32 param_2, i32 param_3, i32 param_4, i32 param_5,
                           i32 param_6, i32 param_7, u32 param_8, u32 param_9, i32 param_10,
                           fnptr_t param_11, i32 param_12)
{
  u16 *puVar1;
  i32 iVar2, iVar3, iVar4, iVar5, iVar6;
  u8 *pbVar7;
  u32 uVar8, uVar10, uVar11, uVar12, uVar14;
  u32 uVar9;
  u16 *puVar13;
  u32 local_2fc;
  i32 local_2f8;
  u32 local_2f0;
  u16 local_2da;
  u32 local_2d8;
  i32 local_2d4;
  i32 local_2d0;
  u8 local_2cc[680];

  (void)param_1;

  local_2da = 0;
  local_2d8 = 0;
  puVar1 = FUN_000478d8(param_2, &local_2da);
  local_2d4 = 0;
  local_2d0 = 0;

  if (param_10 == 0) {
    if (param_11 != 0) goto LAB_00044b96;
    if (param_12 == 0) {
      iVar2 = FUN_000431a8();
      if ((i32)(iVar2 << 30) < 0) {
        FUN_000471cc(*(volatile u32*)0x2000a034UL, 0, param_4, param_5, param_6, param_7);
      }
      uVar14 = 0;
      uVar8 = 0;
      uVar10 = 0;
      local_2fc = 0;
      local_2f0 = 0;
      for (;;) {
        if ((i32)local_2da <= (i32)local_2fc) goto LAB_00044a68;
        uVar11 = (u32)*puVar1;
        iVar2 = FUN_0007d860(uVar11);
        if (iVar2 == 0) {
          iVar3 = FUN_0004588c(param_3, uVar11, &local_2d4, &local_2d0, &local_2d8, 0);
          iVar4 = local_2d0;
          iVar2 = local_2d4;
          if (iVar3 < 0) {
LAB_000448c2:
            if (1 < *(volatile i32*)0x2000230cUL) {
              if (*(volatile i32*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000aaa58UL, 0x000aad78UL, uVar11, 0);
              } else {
                FUN_00019c70();
              }
            }
          } else {
            iVar3 = local_2d4 / 2;
            iVar6 = local_2d0 * iVar3;
            FUN_00086c1e(local_2cc, local_2d8, iVar6, 0x2a4);
            if (local_2fc < param_9) {
              pbVar7 = local_2cc;
              for (iVar5 = 0; iVar5 < iVar6; iVar5 = iVar5 + 1) {
                *pbVar7 = *pbVar7 & *(volatile u8*)0x200034f6UL;
                pbVar7 = pbVar7 + 1;
              }
            }
            iVar6 = FUN_00043e58(*puVar1, puVar1[1]);
            local_2f0 = local_2f0 + iVar2 + iVar6;
            if ((u32)(param_6 - param_4) < local_2f0) {
              uVar14 = uVar14 + 1;
              uVar12 = local_2fc;
              puVar13 = puVar1;
              if ((param_8 <= uVar14) || ((u32)(param_7 - param_5) <= uVar8)) {
                while (uVar12 != 0) {
                  if (3 < (u32)((param_6 - param_4) - (i32)uVar10)) goto LAB_000449e6;
                  uVar11 = (u32)puVar13[-1];
                  iVar2 = FUN_0004588c(param_3, uVar11, &local_2d4, &local_2d0, &local_2d8, 0);
                  uVar12 = uVar12 - 1;
                  if (iVar2 < 0) {
                    if (1 < *(volatile i32*)0x2000230cUL) {
                      if (*(volatile i32*)0x20007554UL == 0) {
                        DEBUG_PRINT(0x000aab9eUL, 0x000aad78UL, uVar12, uVar11);
                      } else {
                        FUN_00019c70();
                      }
                    }
                  } else {
                    iVar2 = FUN_00043e58(puVar13[-1], *puVar13);
                    uVar10 = (uVar10 - (u32)local_2d4) - (u32)iVar2;
                    FUN_000471cc(*(volatile u32*)0x2000a034UL, 0, param_4 + (i32)uVar10, uVar8 + param_5,
                                 local_2d4 + param_4 + (i32)uVar10, local_2d0 + uVar8 + param_5);
                  }
                  puVar13 = puVar13 - 1;
                }
                uVar10 = 0;
LAB_000449e6:
                if (1 < *(volatile i32*)0x2000230cUL) {
                  if (*(volatile i32*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x000aabd2UL, 0x000aad78UL, uVar10, 0);
                  } else {
                    FUN_00019c70();
                  }
                }
                iVar4 = FUN_0004588c(param_3, 0x2026, &local_2d4, &local_2d0, &local_2d8, 0);
                iVar2 = local_2d0;
                if (iVar4 < 0) goto LAB_000448c2;
                iVar4 = local_2d4 / 2;
                iVar3 = local_2d0 * iVar4;
                FUN_00086c1e(local_2cc, local_2d8, iVar3, 0x2a4);
                if (local_2fc < param_9) {
                  pbVar7 = local_2cc;
                  for (local_2f8 = 0; iVar3 - local_2f8 != 0 && local_2f8 <= iVar3; local_2f8 = local_2f8 + 1) {
                    *pbVar7 = *pbVar7 & *(volatile u8*)0x200034f6UL;
                    pbVar7 = pbVar7 + 1;
                  }
                }
                FUN_0007d53a(*(volatile u32*)0x2000a034UL, local_2cc, iVar4, iVar2, (i32)uVar10 + param_4, uVar8 + param_5);
LAB_00044a68:
                iVar2 = FUN_000431a8();
                if (-1 < (i32)(iVar2 << 30)) {
                  return 0;
                }
                iVar2 = FUN_000167a8();
                uVar9 = *(volatile u32*)(iVar2 + 0xeb4);
                iVar2 = FUN_000167a8();
                FUN_00047260(uVar9, *(volatile u32*)(iVar2 + 0xeb8), param_4, param_5, param_6, param_7);
                return 0;
              }
              uVar8 = uVar8 + (u32)iVar4;
              if (param_3 == 0) {
                uVar8 = uVar8 + 1;
              }
              FUN_0007d53a(*(volatile u32*)0x2000a034UL, local_2cc, iVar3, iVar4, param_4, uVar8 + param_5);
              iVar2 = FUN_00043e58(*puVar1, puVar1[1]);
              uVar10 = (u32)local_2d4 + (u32)iVar2;
              local_2f0 = uVar10;
            } else {
              FUN_0007d53a(*(volatile u32*)0x2000a034UL, local_2cc, iVar3, iVar4, (i32)uVar10 + param_4, uVar8 + param_5);
              iVar2 = FUN_00043e58(*puVar1, puVar1[1]);
              uVar10 = uVar10 + (u32)iVar2 + (u32)local_2d4;
            }
          }
        } else if ((iVar2 == -1) && ((uVar11 == 0xd) || (uVar11 == 10))) {
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
          uVar14 = uVar14 + 1;
          if ((param_8 <= uVar14) || ((u32)(param_7 - param_5) <= uVar8)) goto LAB_00044a68;
          uVar10 = 0;
          local_2f0 = 0;
        }
        puVar1 = puVar1 + 1;
        local_2fc = local_2fc + 1;
      }
    }
  } else if (param_11 != 0) {
    goto LAB_00044b96;
  }
  return 0;

LAB_00044b96:
  if (1 < *(volatile i32*)0x2000230cUL) {
    if (*(volatile i32*)0x20007554UL == 0) {
      DEBUG_PRINT(0x000aaa7fUL, 0x000aad78UL, 0, 0);
    } else {
      FUN_00019c70();
    }
  }
  uVar9 = (*param_11)(0, param_2, param_3, param_4, param_5);
  return uVar9;
}

