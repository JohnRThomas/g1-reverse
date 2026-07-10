#include "g1_app_symbols.h"
/* named: gui_utf_draw_dark_light_split */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_utf_draw_dark_light_split @ 0x44544  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort; typedef unsigned char byte;
extern int DEBUG_PRINT(int,...); extern int get_device_info(int,...); extern int debug_print(int,...);
extern int atomic_get_3_0(int,...); extern int count_chars_in_default_font_table(int,...); extern int resource_manger_get(int,...);
extern int clean_fb_data(int,...); extern int reflash_fb_data_to_lcd(int,...); extern int utf8_string_to_utf16(int,...);
extern int fb_blit_rows_copy(int,...); extern int index_in_range32_mask(int,...); extern int FUN_00086c1e(int,...);
typedef undefined4 (*codeptr)(int,...);

undefined4 gui_utf_draw_dark_light_split(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6,
            int param_7,uint param_8,ushort param_9,int param_10,codeptr param_11,int param_12)
{
  int iVar1; ushort *puVar2; int iVar3; int iVar4; int iVar5; uint uVar6; byte *pbVar7;
  uint uVar8; undefined4 uVar9; ushort *puVar10; uint uVar11; int iVar12; uint uVar13; uint uVar14; uint uVar15;
  int local_2ec; ushort local_2da; undefined4 local_2d8; int local_2d4; int local_2d0; byte local_2cc[680];
  uVar6 = (uint)param_9; local_2da = 0; local_2d8 = 0;
  puVar2 = (ushort *)utf8_string_to_utf16(param_2,(int)&local_2da);
  local_2d4 = 0; local_2d0 = 0;
  if (param_10 == 0) {
    if (param_11 != 0) {
LAB_a2:
      if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): exex process effect callback function\n" /*=0xaaa7f*/,"gui_utf_draw_dark_light_split" /*=0xaad8e*/);
        else debug_print(0);
      }
      uVar9 = (*param_11)(0,param_2,param_3,param_4,param_5);
      return uVar9;
    }
    if (param_12 == 0) {
      iVar3 = atomic_get_3_0(0);
      if (iVar3 << 0x1e < 0) clean_fb_data(*(volatile int*)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/,0,param_4,param_5,param_6,param_7);
      uVar11 = 0; uVar15 = 0; uVar8 = 0; uVar14 = 0;
      for (local_2ec = 0; local_2ec < (int)(uint)local_2da; local_2ec = local_2ec + 1) {
        puVar10 = puVar2 + 1; uVar13 = (uint)*puVar2;
        iVar3 = index_in_range32_mask(uVar13);
        if (iVar3 == 0) {
          if (uVar13 == uVar6) {
            iVar3 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/; uVar13 = uVar6;
            if (*(volatile char*)((uintptr_t)&g_gui_dark_light_flag) /*=0x2001cdd4*/ == 0) {
              *(volatile char*)((uintptr_t)&g_gui_dark_light_flag) /*=0x2001cdd4*/ = 1;
              if (1 < iVar3) { iVar3 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/; uVar9 = "%s(): dark_light_flag 1 code = 0x%x\n" /*=0xaab3b*/;
LAB_2c: if (iVar3 == 0) DEBUG_PRINT(uVar9,"gui_utf_draw_dark_light_split" /*=0xaad8e*/,uVar13); else debug_print(0); }
            } else {
              *(volatile char*)((uintptr_t)&g_gui_dark_light_flag) /*=0x2001cdd4*/ = 0;
              if (1 < iVar3) { iVar3 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/; uVar9 = "%s(): dark_light_flag 0 code = 0x%x\n" /*=0xaab60*/; goto LAB_2c; }
            }
          } else {
            iVar4 = resource_manger_get(param_3,uVar13,(int)&local_2d4,(int)&local_2d0,(int)&local_2d8,0);
            iVar1 = local_2d0; iVar3 = local_2d4;
            if (iVar4 < 0) { if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) { iVar3 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/; uVar9 = "%s(): can not find 0x%x font resource\n" /*=0xaaa58*/; goto LAB_2c; } }
            else {
              iVar4 = local_2d4 / 2; iVar5 = local_2d0 * iVar4;
              FUN_00086c1e((int)local_2cc,local_2d8,iVar5,0x2a4);
              if (*(volatile char*)((uintptr_t)&g_gui_dark_light_flag) /*=0x2001cdd4*/ == 1) {
                pbVar7 = local_2cc;
                for (iVar12 = 0; iVar12 < iVar5; iVar12 = iVar12 + 1) { *pbVar7 = *pbVar7 & *(volatile byte*)((uintptr_t)&g_gui_dark_light_dither_mask) /*=0x200034f6*/; pbVar7 = pbVar7 + 1; }
              }
              iVar5 = count_chars_in_default_font_table(*puVar2,*puVar10);
              uVar15 = uVar15 + iVar3 + iVar5;
              if ((uint)(param_6 - param_4) < uVar15) {
                uVar8 = uVar8 + iVar1;
                if (param_3 == 0) uVar8 = uVar8 + 1;
                uVar11 = uVar11 + 1;
                if ((param_8 <= uVar11) || ((uint)(param_7 - param_5) <= uVar8)) break;
                fb_blit_rows_copy(*(volatile int*)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/,(int)local_2cc,iVar4,iVar1,param_4,uVar8 + param_5);
                iVar3 = count_chars_in_default_font_table(*puVar2,*puVar10);
                uVar14 = iVar3 + local_2d4; uVar15 = uVar14;
              } else {
                fb_blit_rows_copy(*(volatile int*)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/,(int)local_2cc,iVar4,iVar1,uVar14 + param_4,uVar8 + param_5);
                iVar3 = count_chars_in_default_font_table(*puVar2,*puVar10);
                uVar14 = uVar14 + iVar3 + local_2d4;
              }
            }
          }
        } else if ((iVar3 == -1) && ((uVar13 == 0xd || (uVar13 == 10)))) {
          if (local_2d0 == 0) { if (param_3 == 0) uVar8 = uVar8 + 0x1b; else uVar8 = uVar8 + 0x1a; }
          else { uVar8 = uVar8 + local_2d0; if (param_3 == 0) uVar8 = uVar8 + 1; }
          uVar11 = uVar11 + 1;
          if ((param_8 <= uVar11) || ((uint)(param_7 - param_5) <= uVar8)) break;
          uVar14 = 0; uVar15 = uVar14;
        }
        puVar2 = puVar10;
      }
      iVar3 = atomic_get_3_0(0);
      if (iVar3 << 0x1e < 0) {
        iVar3 = get_device_info(0); uVar9 = *(undefined4 *)(iVar3 + 0xeb4);
        iVar3 = get_device_info(0);
        reflash_fb_data_to_lcd(uVar9,*(undefined4 *)(iVar3 + 0xeb8),param_4,param_5,param_6,param_7);
      }
    }
  }
  else if (param_11 != 0) goto LAB_a2;
  *(volatile char*)((uintptr_t)&g_gui_dark_light_flag) /*=0x2001cdd4*/ = 0;
  if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): dark_light_flag 0\n" /*=0xaab85*/,"gui_utf_draw_dark_light_split" /*=0xaad8e*/);
    else debug_print(0);
  }
  return 0;
}

