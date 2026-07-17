#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000451e0 @ 0x000451e0
 * public-name: gui_utf_Wordwrap_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   count_chars_in_default_font_table        <= FUN_00043e58 @ 0x00043e58
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   utf8_string_to_utf16                     <= FUN_000478d8 @ 0x000478d8
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 *   index_in_range32_mask                    <= FUN_0007d860 @ 0x0007d860
 * address symbols (name @ address):
 *   rodata_88434                             @ 0x00088434
 *   rodata_8843e                             @ 0x0008843e
 *   rodata_aaa58                             @ 0x000aaa58
 *   rodata_aaa7f                             @ 0x000aaa7f
 *   rodata_aac1e                             @ 0x000aac1e
 *   rodata_aad35                             @ 0x000aad35
 *   g_log_level                              @ 0x2000230c
 *   g_gui_dark_light_dither_mask             @ 0x200034f6
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed gui_utf_Wordwrap_draw @ 0x451e0  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;

extern void DEBUG_PRINT(u32,u32);
extern u32 get_device_info(void);
extern void debug_print(void);
extern u32 atomic_get_3_0(void);
extern u32 count_chars_in_default_font_table(u32,u32);
extern i32 resource_manger_get(u32,u32,void*,void*,void*,u32);
extern void clean_fb_data(u32,u32,u32,u32,u32,u32);
extern void reflash_fb_data_to_lcd(u32,u32,u32,u32,u32,u32);
extern u16* utf8_string_to_utf16(u32,void*);
extern void fb_blit_rows_copy(u32,void*,u32,u32,u32,u32);
extern u32 index_in_range32_mask(u32);
extern void FUN_00086c1e(void*,u32,u32,u32);

typedef u32 (*fnptr_t)(u32,u32,u32,u32,u32);

static u16 tbl1(u32 i) { return *(volatile u16*)(((unsigned long)&rodata_88434) /*=0x88434*/ + 2u*i); }
static u16 tbl2(u32 i) { return *(volatile u16*)(((unsigned long)&rodata_8843e) /*=0x8843e*/ + 2u*i); }

u32 gui_utf_Wordwrap_draw(u32 param_1, u32 param_2, i32 param_3, i32 param_4, i32 param_5,
                           i32 param_6, i32 param_7, u32 param_8, u32 param_9, i32 param_10,
                           fnptr_t param_11, i32 param_12)
{
  u16 *puVar2;
  i32 iVar3;
  u16 *puVar4;
  u16 *puVar17;
  u32 uVar7 = 0, uVar8, uVar12, uVar13x, uVar14, uVar15, uVar16, uVar18, uVar19;
  u8 *pbVar9;
  u32 uVar13;
  int bVar20;
  u32 local_318;
  u32 local_314;
  u16 local_302;
  u32 local_300;
  i32 local_2fc;
  i32 local_2f8;
  i32 local_2f4_0, local_2f4_1;
  u32 auStack_2ec;
  u32 idx1, idx2;
  u8 local_2cc[680];
  i32 iVar5;

  (void)param_1;

  local_302 = 0;
  local_300 = 0;
  puVar2 = utf8_string_to_utf16(param_2, &local_302);
  local_2fc = 0;
  local_2f8 = 0;

  if (param_10 == 0) {
    if (param_11 != 0) goto LAB_0004558c;
    if (param_12 == 0) {
      iVar3 = atomic_get_3_0();
      if ((i32)(iVar3 << 30) < 0) {
        clean_fb_data(*(volatile u32*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, 0, param_4, param_5, param_6, param_7);
      }
      uVar14 = 0;
      uVar15 = 0;
      uVar12 = 0;
      uVar19 = 0;
      uVar8 = (u32)(param_6 - param_4);
      puVar17 = puVar2;
      for (uVar18 = 0; (i32)uVar18 < (i32)(u32)local_302; uVar18 = uVar18 + 1) {
        uVar16 = (u32)*puVar17;
        iVar3 = index_in_range32_mask(uVar16);
        if (iVar3 == 0) {
          iVar3 = resource_manger_get(param_3, uVar16, &local_2fc, &local_2f8, &local_300, 0);
          if (iVar3 < 0) {
            if (1 < *(volatile i32*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
              if (*(volatile i32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT(((unsigned long)&rodata_aaa58) /*=0xaaa58*/, ((unsigned long)&rodata_aad35) /*=0xaad35*/);
              } else {
                debug_print();
              }
            }
          } else {
            iVar3 = local_2f8 * (local_2fc / 2);
            FUN_00086c1e(local_2cc, local_300, iVar3, 0x2a4);
            if (uVar18 < param_9) {
              pbVar9 = local_2cc;
              for (iVar5 = 0; iVar3 - iVar5 != 0 && iVar5 <= iVar3; iVar5 = iVar5 + 1) {
                *pbVar9 = *pbVar9 & *(volatile u8*)((unsigned long)&g_gui_dark_light_dither_mask) /*=0x200034f6*/;
                pbVar9 = pbVar9 + 1;
              }
            }
            bVar20 = 0;
            if (((uVar8 >> 1) < uVar15) && (uVar14 < param_8 - 1)) {
              idx1 = 0;
LAB_000453d8:
              if (tbl1(idx1) != uVar16) goto code_r0x000453e0;
              if (uVar16 == 0) goto LAB_00045314;
              uVar7 = uVar18 + 1;
              uVar16 = uVar7;
              goto LAB_00045412;
code_r0x000453e0:
              idx1 = idx1 + 1;
              if (idx1 == 5) goto LAB_00045314;
              goto LAB_000453d8;

LAB_00045412:
              if ((i32)uVar16 < (i32)(u32)local_302) {
                idx2 = 0;
LAB_00045422:
                if (puVar2[uVar16] != tbl2(idx2)) goto LAB_0004543c;
                if (puVar2[uVar16] == 0) goto LAB_00045442;
                if (0x28 < (i32)(uVar16 - uVar18)) {
                  if (*(volatile i32*)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) goto LAB_00045314;
                  iVar3 = *(volatile i32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                  uVar13 = 0x000aabe8UL;
                  goto LAB_00045458;
                }
                iVar3 = 0;
                while ((i32)uVar7 < (i32)uVar16) {
                  puVar4 = puVar2 + uVar7;
                  uVar7 = uVar7 + 1;
                  if (0x25cc < *puVar4) {
                    iVar3 = iVar3 + 1;
                  }
                }
                if (uVar18 == uVar16) {
                  if (1 < *(volatile i32*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
                    iVar3 = *(volatile i32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                    uVar13 = ((unsigned long)&rodata_aac1e) /*=0xaac1e*/;
LAB_00045458:
                    if (iVar3 == 0) {
                      DEBUG_PRINT(uVar13, ((unsigned long)&rodata_aad35) /*=0xaad35*/);
                    } else {
                      debug_print();
                    }
                  }
                } else {
                  if ((iVar3 != 0) &&
                      !((float)iVar3 / (float)(i32)(uVar16 - uVar18) < 0.5f)) {
                    goto LAB_00045314;
                  }
                  local_2f4_0 = 0;
                  local_2f4_1 = 0;
                  puVar4 = puVar17;
                  local_318 = uVar15;
                  for (local_314 = uVar18; (i32)local_314 <= (i32)uVar16; local_314 = local_314 + 1) {
                    iVar3 = resource_manger_get(param_3, *puVar4, &local_2f4_0, &local_2f4_1, &auStack_2ec, 0);
                    if (iVar3 == 0) {
                      iVar3 = count_chars_in_default_font_table(*puVar4, puVar4[1]);
                      local_318 = local_318 + (u32)iVar3 + (u32)local_2f4_0;
                    }
                    if (uVar8 < local_318) {
                      bVar20 = 1;
                      break;
                    }
                    puVar4 = puVar4 + 1;
                  }
                }
                goto LAB_00045314;
LAB_0004543c:
                idx2 = idx2 + 1;
                if (idx2 == 7) goto LAB_00045442;
                goto LAB_00045422;
LAB_00045442:
                uVar16 = uVar16 + 1;
                goto LAB_00045412;
              }
            }
LAB_00045314:
            iVar3 = count_chars_in_default_font_table(*puVar17, puVar17[1]);
            uVar15 = uVar15 + (u32)iVar3 + (u32)local_2fc;
            if (uVar8 < uVar15) {
              uVar12 = uVar12 + (u32)local_2f8;
              if (param_3 == 0) {
                uVar12 = uVar12 + 1;
              }
              uVar14 = uVar14 + 1;
              if ((param_8 <= uVar14) || ((u32)(param_7 - param_5) <= uVar12)) break;
              fb_blit_rows_copy(*(volatile u32*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, local_2cc, local_2fc / 2, local_2f8, param_4, uVar12 + param_5);
              iVar3 = count_chars_in_default_font_table(*puVar17, puVar17[1]);
              uVar15 = (u32)iVar3 + (u32)local_2fc;
              uVar19 = uVar15;
            } else {
              fb_blit_rows_copy(*(volatile u32*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, local_2cc, local_2fc / 2, local_2f8, param_4 + (i32)uVar19, uVar12 + param_5);
              iVar3 = count_chars_in_default_font_table(*puVar17, puVar17[1]);
              uVar19 = uVar19 + (u32)iVar3 + (u32)local_2fc;
            }
LAB_0004537a:
            if (bVar20) goto LAB_0004537c;
          }
        } else if (iVar3 == -1) {
          if (uVar16 != 10) {
            bVar20 = (uVar16 == 0xd);
            goto LAB_0004537a;
          }
LAB_0004537c:
          if (local_2f8 == 0) {
            if (param_3 == 0) {
              uVar12 = uVar12 + 0x1b;
            } else {
              uVar12 = uVar12 + 0x1a;
            }
          } else {
            uVar12 = uVar12 + (u32)local_2f8;
            if (param_3 == 0) {
              uVar12 = uVar12 + 1;
            }
          }
          uVar14 = uVar14 + 1;
          if ((param_8 <= uVar14) || ((u32)(param_7 - param_5) <= uVar12)) break;
          uVar15 = 0;
          uVar19 = uVar15;
        }
        puVar17 = puVar17 + 1;
      }
      iVar3 = atomic_get_3_0();
      if ((i32)(iVar3 << 30) < 0) {
        iVar3 = get_device_info();
        uVar13x = *(volatile u32*)(iVar3 + 0xeb4);
        iVar3 = get_device_info();
        reflash_fb_data_to_lcd(uVar13x, *(volatile u32*)(iVar3 + 0xeb8), param_4, param_5, param_6, param_7);
      }
    }
  } else if (param_11 != 0) {
    goto LAB_0004558c;
  }
  return 0;

LAB_0004558c:
  if (1 < *(volatile i32*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
    if (*(volatile i32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT(((unsigned long)&rodata_aaa7f) /*=0xaaa7f*/, ((unsigned long)&rodata_aad35) /*=0xaad35*/);
    } else {
      debug_print();
    }
  }
  uVar13x = (*param_11)(0, param_2, param_3, param_4, param_5);
  return uVar13x;
}
