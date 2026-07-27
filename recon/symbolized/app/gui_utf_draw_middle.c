#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00044bd8 @ 0x00044bd8
 * public-name: gui_utf_draw_middle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   count_chars_in_default_font_table        <= FUN_00043e58 @ 0x00043e58
 *   gui_utf_draw_middle                      <= FUN_00044bd8 @ 0x00044bd8
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   utf8_string_to_utf16                     <= FUN_000478d8 @ 0x000478d8
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 *   index_in_range32_mask                    <= FUN_0007d860 @ 0x0007d860
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 * address symbols (name @ address):
 *   rodata_aaa58                             @ 0x000aaa58
 *   rodata_aaa7f                             @ 0x000aaa7f   [INLINED -- G6 literal batch]
 *   rodata_aad64                             @ 0x000aad64   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_gui_dark_light_dither_mask             @ 0x200034f6
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_00044bd8 @ 0x44bd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort; typedef unsigned char byte;
extern int get_device_info(int,...);
extern int atomic_get_3_0(int,...); extern int count_chars_in_default_font_table(int,...); extern long resource_manger_get(unsigned long, unsigned long, long*, long*, unsigned long*, unsigned long);
extern int clean_fb_data(int,...); extern int reflash_fb_data_to_lcd(int,...); extern int utf8_string_to_utf16(int,...);
extern int fb_blit_rows_copy(int, int, int, int, int, int); extern int index_in_range32_mask(int,...); extern int safe_memcpy_checked(int,...);
typedef undefined4 (*codeptr)(int,...);

undefined4 gui_utf_draw_middle(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6,
            int param_7,uint param_8,uint param_9,int param_10,codeptr param_11,int param_12)
{
  int iVar1; ushort *puVar2; int iVar3; int iVar4; int iVar5; int bVar6; byte *pbVar7;
  uint uVar8; undefined4 uVar9; uint uVar10; uint uVar11; uint uVar12; int iVar13; uint uVar14; uint uVar15;
  ushort *puVar16; ushort *puVar17; uint uVar18;
  uint local_2f4; int local_2f0; ushort local_2da; undefined4 local_2d8; int local_2d4; int local_2d0; byte local_2cc[680];
  local_2da = 0; local_2d8 = 0;
  puVar2 = (ushort *)utf8_string_to_utf16(param_2,(int)&local_2da);
  local_2d4 = 0; local_2d0 = 0;
  if (param_10 == 0) {
    if (param_11 != 0) {
LAB_e7c:
      if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)"%s(): exex process effect callback function\n") /*=0xaaa7f*/,((unsigned long)"gui_utf_draw_middle") /*=0xaad64*/);
        else debug_print(((unsigned long)"%s(): exex process effect callback function\n") /*=0xaaa7f*/,((unsigned long)"gui_utf_draw_middle") /*=0xaad64*/);
      }
      uVar9 = (*param_11)(0,param_2,param_3,param_4,param_5);
      return uVar9;
    }
    if (param_12 == 0) {
      iVar3 = atomic_get_3_0(0);
      if (iVar3 << 0x1e < 0) clean_fb_data(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,0,param_4,param_5,param_6,param_7);
      uVar10 = 0; uVar18 = 0; uVar8 = 0; bVar6 = 1; uVar11 = 0; puVar16 = puVar2; local_2f0 = param_4;
      for (local_2f4 = 0; (int)local_2f4 < (int)(uint)local_2da; local_2f4 = local_2f4 + 1) {
        if (bVar6) {
          uVar12 = 0;
          for (uVar14 = local_2f4; (((int)uVar14 < (int)(uint)local_2da && (uVar15 = (uint)puVar2[uVar14], uVar15 != 0xd)) && (uVar15 != 10)); uVar14 = uVar14 + 1) {
            iVar3 = index_in_range32_mask(uVar15);
            if (iVar3 == 0) {
              iVar3 = resource_manger_get(param_3,uVar15,(int)&local_2d4,(int)&local_2d0,(int)&local_2d8,0);
              if (iVar3 < 0) {
                if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) { if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)&rodata_aaa58) /*=0xaaa58*/,((unsigned long)"gui_utf_draw_middle") /*=0xaad64*/,uVar15); else debug_print(((unsigned long)&rodata_aaa58) /*=0xaaa58*/,((unsigned long)"gui_utf_draw_middle") /*=0xaad64*/,uVar15); }
              } else uVar12 = local_2d4 + uVar12 & 0xffff;
            }
          }
          local_2f0 = param_4 + (int)(0x240 - uVar12) / 2;
        }
        puVar17 = puVar16 + 1; uVar14 = (uint)*puVar16;
        iVar3 = index_in_range32_mask(uVar14);
        if (iVar3 == 0) {
          iVar4 = resource_manger_get(param_3,uVar14,(int)&local_2d4,(int)&local_2d0,(int)&local_2d8,0);
          iVar1 = local_2d0; iVar3 = local_2d4;
          if (iVar4 < 0) {
            if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) { if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)&rodata_aaa58) /*=0xaaa58*/,((unsigned long)"gui_utf_draw_middle") /*=0xaad64*/,uVar14); else debug_print(((unsigned long)&rodata_aaa58) /*=0xaaa58*/,((unsigned long)"gui_utf_draw_middle") /*=0xaad64*/,uVar14); }
          } else {
            iVar4 = local_2d4 / 2; iVar5 = local_2d0 * iVar4;
            safe_memcpy_checked((int)local_2cc,local_2d8,iVar5,0x2a4);
            if (local_2f4 < param_9) { pbVar7 = local_2cc; for (iVar13 = 0; iVar13 < iVar5; iVar13 = iVar13 + 1) { *pbVar7 = *pbVar7 & *(volatile byte*)((unsigned long)&g_gui_dark_light_dither_mask) /*=0x200034f6*/; pbVar7 = pbVar7 + 1; } }
            iVar5 = count_chars_in_default_font_table(*puVar16,*puVar17);
            uVar18 = uVar18 + iVar3 + iVar5;
            if ((uint)(param_6 - param_4) < uVar18) {
              uVar8 = uVar8 + iVar1; if (param_3 == 0) uVar8 = uVar8 + 1;
              uVar10 = uVar10 + 1;
              if ((param_8 <= uVar10) || ((uint)(param_7 - param_5) <= uVar8)) break;
              fb_blit_rows_copy(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,(int)local_2cc,iVar4,iVar1,local_2f0,uVar8 + param_5);
              iVar3 = count_chars_in_default_font_table(*puVar16,*puVar17); uVar11 = local_2d4 + iVar3; uVar18 = uVar11;
            } else {
              fb_blit_rows_copy(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,(int)local_2cc,iVar4,iVar1,local_2f0 + uVar11,uVar8 + param_5);
              iVar3 = count_chars_in_default_font_table(*puVar16,*puVar17); uVar11 = uVar11 + iVar3 + local_2d4;
            }
          }
LAB_d36: bVar6 = 0;
        } else {
          if ((iVar3 != -1) || ((uVar14 != 0xd && (uVar14 != 10)))) goto LAB_d36;
          if (local_2d0 == 0) { if (param_3 == 0) uVar8 = uVar8 + 0x1b; else uVar8 = uVar8 + 0x1a; }
          else { uVar8 = uVar8 + local_2d0; if (param_3 == 0) uVar8 = uVar8 + 1; }
          uVar10 = uVar10 + 1;
          if ((param_8 <= uVar10) || ((uint)(param_7 - param_5) <= uVar8)) break;
          uVar18 = 0; uVar11 = 0; bVar6 = 1;
        }
        puVar16 = puVar17;
      }
      iVar3 = atomic_get_3_0(0);
      if (iVar3 << 0x1e < 0) {
        iVar3 = get_device_info(0); uVar9 = *(undefined4 *)(iVar3 + 0xeb4);
        iVar3 = get_device_info(0);
        reflash_fb_data_to_lcd(uVar9,*(undefined4 *)(iVar3 + 0xeb8),param_4,param_5,param_6,param_7);
      }
    }
  }
  else if (param_11 != 0) goto LAB_e7c;
  return 0;
}
