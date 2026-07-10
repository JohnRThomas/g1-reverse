#include "g1_app_symbols.h"
/* named: gui_utf_draw_align_right */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_utf_draw_align_right @ 0x44ec4  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;

extern void DEBUG_PRINT(u32,u32,u32,u32);
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
  puVar2 = utf8_string_to_utf16(param_2, &local_2da);
  local_2d4 = 0;
  local_2d0 = 0;

  if (param_10 == 0) {
    if (param_11 != 0) goto LAB_000451a2;
    if (param_12 == 0) {
      iVar3 = atomic_get_3_0();
      if ((i32)(iVar3 << 30) < 0) {
        clean_fb_data(*(volatile u32*)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/, 0, param_4, param_5, param_6, param_7);
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
            iVar3 = index_in_range32_mask(uVar15);
            if (iVar3 == 0) {
              iVar3 = resource_manger_get(param_3, uVar15, &local_2d4, &local_2d0, &local_2d8, 0);
              if (iVar3 < 0) {
                if (1 < *(volatile i32*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                  if (*(volatile i32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): can not find 0x%x font resource\n" /*=0xaaa58*/, "gui_utf_draw_align_right" /*=0xaad4b*/, uVar15, 0);
                  } else {
                    debug_print();
                  }
                }
              } else {
                uVar11 = uVar11 + (u32)local_2d4;
                iVar3 = count_chars_in_default_font_table(*puVar13, puVar13[1]);
                uVar11 = ((uVar11 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/) + (u32)iVar3) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
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
        iVar3 = index_in_range32_mask(uVar14);
        if (iVar3 == 0) {
          iVar4 = resource_manger_get(param_3, uVar14, &local_2d4, &local_2d0, &local_2d8, 0);
          iVar1 = local_2d0;
          iVar3 = local_2d4;
          if (iVar4 < 0) {
            if (1 < *(volatile i32*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
              if (*(volatile i32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): can not find 0x%x font resource\n" /*=0xaaa58*/, "gui_utf_draw_align_right" /*=0xaad4b*/, uVar14, 0);
              } else {
                debug_print();
              }
            }
          } else {
            iVar4 = local_2d4 / 2;
            iVar5 = local_2d0 * iVar4;
            FUN_00086c1e(local_2cc, local_2d8, iVar5, 0x2a4);
            if (local_2ec < param_9) {
              pbVar7 = local_2cc;
              for (iVar12 = 0; iVar12 < iVar5; iVar12 = iVar12 + 1) {
                *pbVar7 = *pbVar7 & *(volatile u8*)((uintptr_t)&g_gui_dark_light_dither_mask) /*=0x200034f6*/;
                pbVar7 = pbVar7 + 1;
              }
            }
            iVar5 = count_chars_in_default_font_table(*puVar2, *puVar13);
            local_2f4 = local_2f4 + (u32)iVar5 + (u32)iVar3;
            if ((u32)(param_6 - (i32)param_4) < local_2f4) {
              uVar8 = uVar8 + (u32)iVar1;
              if (param_3 == 0) {
                uVar8 = uVar8 + 1;
              }
              uVar10 = uVar10 + 1;
              if ((param_8 <= uVar10) || ((u32)(param_7 - param_5) <= uVar8)) break;
              fb_blit_rows_copy(*(volatile u32*)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/, local_2cc, iVar4, iVar1, local_2e8, uVar8 + param_5);
              iVar3 = count_chars_in_default_font_table(*puVar2, *puVar13);
              local_2f8 = (u32)iVar3 + (u32)local_2d4;
              local_2f4 = local_2f8;
            } else {
              fb_blit_rows_copy(*(volatile u32*)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/, local_2cc, iVar4, iVar1, local_2e8 + local_2f8, uVar8 + param_5);
              iVar3 = count_chars_in_default_font_table(*puVar2, *puVar13);
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
      iVar3 = atomic_get_3_0();
      if ((i32)(iVar3 << 30) < 0) {
        iVar3 = get_device_info();
        uVar9 = *(volatile u32*)(iVar3 + 0xeb4);
        iVar3 = get_device_info();
        reflash_fb_data_to_lcd(uVar9, *(volatile u32*)(iVar3 + 0xeb8), param_4, param_5, param_6, param_7);
      }
    }
  } else if (param_11 != 0) {
    goto LAB_000451a2;
  }
  return 0;

LAB_000451a2:
  if (1 < *(volatile i32*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
    if (*(volatile i32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT("%s(): exex process effect callback function\n" /*=0xaaa7f*/, "gui_utf_draw_align_right" /*=0xaad4b*/, 0, 0);
    } else {
      debug_print();
    }
  }
  uVar9 = (*param_11)(0, param_2, param_3, param_4, param_5);
  return uVar9;
}

