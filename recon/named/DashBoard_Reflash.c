/* readable reconstruction; identity: FUN_0003727c @ 0x0003727c
 * public-name: DashBoard_Reflash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   check_charging_and_touch_flags           <= FUN_00026c28 @ 0x00026c28
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   draw_quicknote_hint_on_dashboard         <= FUN_00036d38 @ 0x00036d38
 *   reset_touch_selection_state              <= FUN_00037098 @ 0x00037098
 *   cleanStocksIndex                         <= FUN_00037154 @ 0x00037154
 *   cleanNewsIndex                           <= FUN_00037234 @ 0x00037234
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_area_clear                           <= FUN_00043228 @ 0x00043228
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_bitmap_draw                          <= FUN_00043a68 @ 0x00043a68
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   gui_utf_draw_dark_light_split            <= FUN_00044544 @ 0x00044544
 *   gui_utf_draw_align_right                 <= FUN_00044ec4 @ 0x00044ec4
 *   gui_string_draw                          <= FUN_000455cc @ 0x000455cc
 *   dashboard_reflash_index_lookup           <= FUN_000469a8 @ 0x000469a8
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   dashboard_read_word                      <= FUN_0007d1d0 @ 0x0007d1d0
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   compute_day_of_week                      <= FUN_0007d280 @ 0x0007d280
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   get_localized_weekday_name               <= FUN_0007d4b2 @ 0x0007d4b2
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 * address symbols (name @ address):
 *   rodata_a8ea1                             @ 0x000a8ea1
 *   rodata_a8eb5                             @ 0x000a8eb5
 *   rodata_a8ec6                             @ 0x000a8ec6
 *   rodata_a8edd                             @ 0x000a8edd
 *   rodata_a9009                             @ 0x000a9009   [INLINED -- G6 literal batch]
 *   rodata_a9014                             @ 0x000a9014   [INLINED -- G6 literal batch]
 *   rodata_a902d                             @ 0x000a902d   [INLINED -- G6 literal batch]
 *   rodata_a904c                             @ 0x000a904c   [INLINED -- G6 literal batch]
 *   rodata_a9078                             @ 0x000a9078   [INLINED -- G6 literal batch]
 *   rodata_a9082                             @ 0x000a9082   [INLINED -- G6 literal batch]
 *   rodata_a909f                             @ 0x000a909f   [INLINED -- G6 literal batch]
 *   rodata_a90b7                             @ 0x000a90b7   [INLINED -- G6 literal batch]
 *   rodata_a90de                             @ 0x000a90de   [INLINED -- G6 literal batch]
 *   rodata_a9100                             @ 0x000a9100   [INLINED -- G6 literal batch]
 *   rodata_a9121                             @ 0x000a9121   [INLINED -- G6 literal batch]
 *   rodata_a9127                             @ 0x000a9127   [INLINED -- G6 literal batch]
 *   rodata_a914d                             @ 0x000a914d   [INLINED -- G6 literal batch]
 *   rodata_a9155                             @ 0x000a9155   [INLINED -- G6 literal batch]
 *   rodata_a915b                             @ 0x000a915b   [INLINED -- G6 literal batch]
 *   rodata_a916c                             @ 0x000a916c   [INLINED -- G6 literal batch]
 *   rodata_a917d                             @ 0x000a917d   [INLINED -- G6 literal batch]
 *   rodata_a9195                             @ 0x000a9195   [INLINED -- G6 literal batch]
 *   rodata_a91a4                             @ 0x000a91a4   [INLINED -- G6 literal batch]
 *   rodata_a91c0                             @ 0x000a91c0   [INLINED -- G6 literal batch]
 *   rodata_a91db                             @ 0x000a91db   [INLINED -- G6 literal batch]
 *   rodata_a91f2                             @ 0x000a91f2   [INLINED -- G6 literal batch]
 *   rodata_a9206                             @ 0x000a9206   [INLINED -- G6 literal batch]
 *   rodata_a9219                             @ 0x000a9219   [INLINED -- G6 literal batch]
 *   rodata_a922b                             @ 0x000a922b   [INLINED -- G6 literal batch]
 *   rodata_a95e7                             @ 0x000a95e7   [INLINED -- G6 literal batch]
 *   rodata_f26c1                             @ 0x000f26c1
 *   rodata_f7b6f                             @ 0x000f7b6f
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_canvas_flags                       @ 0x2000a030
 *   g_2000d716                               @ 0x2000d716
 *   g_200107e3                               @ 0x200107e3
 *   g_2001197a                               @ 0x2001197a
 *   g_200119ba                               @ 0x200119ba
 *   g_200119da                               @ 0x200119da
 */
/* Reconstructed DashBoard_Reflash @ 0x3727c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
#pragma GCC diagnostic warning "-Wreturn-type"
#pragma GCC diagnostic warning "-Wbuiltin-declaration-mismatch"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong;
#define CONCAT11(a,b) ((ushort)(((ushort)(uint8_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint)(((uint)(ushort)(a)<<16)|(ushort)(b)))
extern long long strlen(int, ...);
extern long long get_device_info(int, ...);
extern long long get_ui_mode_flag_byte1(int, ...);
extern long long check_charging_and_touch_flags(int, ...);
extern long long msg_content_recalc_unread(int, ...);
extern long long draw_quicknote_hint_on_dashboard(int, ...);
extern long long reset_touch_selection_state(int, ...);
extern long long cleanStocksIndex(int, ...);
extern long long cleanNewsIndex(int, ...);
extern long long gui_screen_clear(int, ...);
extern long long gui_area_clear(int, ...);
extern long long gui_bmp_bitmap_draw(int, ...);
extern long long gui_bitmap_draw(int, ...);
extern long long gui_utf_draw(int, ...);
extern long long gui_clock_draw(int, ...);
extern long long gui_utf_draw_dark_light_split(int, ...);
extern long long gui_utf_draw_align_right(int, ...);
extern long long gui_string_draw(int, ...);
extern long long dashboard_reflash_index_lookup(int, ...);
extern long long clean_fb_data(int, ...);
extern long long reflash_fb_data_to_lcd(int, ...);
extern long long unix_timestamp_to_datetime(int, ...);
extern long long snprintf(int, ...);
extern long long dashboard_read_word(int, ...);
extern long long get_timestamp(int, ...);
extern long long compute_day_of_week(int, ...);
extern long long device_info_text_width_get(int, ...);
extern long long device_info_text_height_get_clamped(int, ...);
extern long long get_localized_weekday_name(int, ...);
extern long long memcpy(int, ...);
extern long long safe_memcpy_checked(int, ...);
extern long long memset_bytes(int, ...);
extern long long vdprintf_to_fd(int, ...);
#define DAT_000374c0 ((volatile int*)0x2000230cUL)
#define DAT_000374c4 ((volatile int*)0x20007554UL)
#define DAT_000374c8 (0xa95e7UL)
#define DAT_000374cc (0xa9014UL)
#define DAT_000374d0 ((volatile int*)0xa900cUL)
#define DAT_000374d4 ((volatile int*)0xa9009UL)
#define DAT_000374d8 (0xa902dUL)
#define DAT_000374dc ((volatile int*)0x20004950UL)
#define DAT_000374e0 (0xa904cUL)
#define DAT_000374e4 (0xa9078UL)
#define DAT_000374e8 (0xa90deUL)
#define DAT_000374ec (0xa9100UL)
#define DAT_000374f0 (0x2000a030UL)
#define DAT_00037918 ((volatile int*)0xa9009UL)
#define DAT_0003791c (0xa95e7UL)
#define DAT_00037920 (0xa902dUL)
#define DAT_00037924 ((volatile int*)0x20007554UL)
#define DAT_00037928 (0xa9082UL)
#define DAT_0003792c (0xa909fUL)
#define DAT_00037930 (0xf26c1UL)
#define DAT_00037938 ((volatile int*)0xa914dUL)
#define DAT_0003793c ((volatile int*)0xa9155UL)
#define DAT_00037c0c ((volatile int*)0x20007554UL)
#define DAT_00037c10 (0xa95e7UL)
#define DAT_00037c14 (0xa90b7UL)
#define DAT_00037c18 (0xf26c1UL)
#define DAT_00037c1c ((volatile int*)0xa915bUL)
#define DAT_00037c20 ((volatile int*)0xa917dUL)
#define DAT_00037c24 ((volatile int*)0xa9219UL)
#define DAT_00037c28 ((volatile int*)0xa922bUL)
#define DAT_00037c2c (0x2001197aUL)
#define DAT_00037c30 (0x200119baUL)
#define DAT_00037c34 (0x200119daUL)
#define DAT_00037e9c (0xa9121UL)
#define DAT_00037ea0 ((volatile int*)0xf7b6fUL)
#define DAT_00037ea4 ((volatile int*)0x20007554UL)
#define DAT_00037ea8 (0xa95e7UL)
#define DAT_00037eac (0xa9127UL)
#define DAT_00037eb0 ((volatile int*)0xa914dUL)
#define DAT_00037eb4 ((volatile int*)0xa9155UL)
#define DAT_00037eb8 ((volatile int*)0x2000d716UL)
#define DAT_00038268 ((volatile int*)0x20007554UL)
#define DAT_0003826c (0xa95e7UL)
#define DAT_00038270 (0xa9127UL)
#define DAT_00038274 (0xa915bUL)
#define DAT_00038278 ((volatile int*)0xa916cUL)
#define DAT_0003827c (0xa9121UL)
#define DAT_00038600 ((volatile int*)0x20007554UL)
#define DAT_00038604 (0xa95e7UL)
#define DAT_00038608 (0xa91a4UL)
#define DAT_0003860c (0xa917dUL)
#define DAT_00038610 ((volatile int*)0xa9195UL)
#define DAT_00038614 (0xa91c0UL)
#define DAT_00038618 (0x2000a030UL)
#define DAT_0003861c ((volatile int*)0x200107e3UL)
#define DAT_00038748 (0xa9121UL)
#define DAT_0003874c ((volatile int*)0xf7b6fUL)
#define DAT_00038adc (0xa9078UL)
#define DAT_00038ae0 ((volatile int*)0x20007554UL)
#define DAT_00038ae4 (0xa95e7UL)
#define DAT_00038ae8 (0xa90deUL)
#define DAT_00038aec (0xa9100UL)
#define DAT_00038af0 (0x2000a030UL)
#define DAT_00038af4 (0xa8ea1UL)
#define DAT_00038af8 ((volatile int*)0xa8eb5UL)
#define DAT_00038f4c (0xa8ec6UL)
#define DAT_00038f50 (0xa9121UL)
#define DAT_00038f54 ((volatile int*)0xf7b6fUL)
#define DAT_00038f58 ((volatile int*)0xa91dbUL)
#define DAT_00038f5c (0xa91f2UL)
#define DAT_00038f60 ((volatile int*)0xa9206UL)
#define DAT_0003925c ((volatile int*)0x20007554UL)
#define DAT_00039260 ((volatile int*)0xa900cUL)
#define DAT_00039264 ((volatile int*)0xa9009UL)
#define DAT_00039268 (0xa95e7UL)
#define DAT_0003926c (0xa902dUL)
#define DAT_00039270 ((volatile int*)0x20004950UL)
#define DAT_00039274 (0xa904cUL)
#define DAT_00039278 (0xa9078UL)
#define DAT_0003927c (0xa90deUL)
#define DAT_00039280 (0xa9100UL)
#define DAT_00039284 (0x2000a030UL)
#define DAT_00039614 (0xa8ea1UL)
#define DAT_00039618 ((volatile int*)0xa9009UL)
#define DAT_0003961c (0xa95e7UL)
#define DAT_00039620 (0xa902dUL)
#define DAT_00039624 ((volatile int*)0x20007554UL)
#define DAT_00039628 (0xa9082UL)
#define DAT_0003962c (0xa909fUL)
#define DAT_00039630 (0xf26c1UL)
#define DAT_00039638 (0xa90b7UL)
#define DAT_00039a14 (0xa8ec6UL)
#define DAT_00039a18 ((volatile int*)0xa8eddUL)
#define DAT_00039a1c (0xa9121UL)
#define DAT_00039a20 ((volatile int*)0x20007554UL)
#define DAT_00039a24 (0xa95e7UL)
#define DAT_00039a28 (0xa9127UL)
#define DAT_00039a2c (0xa915bUL)
#define DAT_00039a30 ((volatile int*)0x2000d716UL)
#define DAT_00039df4 (0xa9121UL)
#define DAT_00039df8 ((volatile int*)0x20007554UL)
#define DAT_00039dfc (0xa95e7UL)
#define DAT_00039e00 (0xa91a4UL)
#define DAT_00039e04 ((volatile int*)0x200107e3UL)
#define DAT_0003a184 (0xa917dUL)
#define DAT_0003a188 ((volatile int*)0x20007554UL)
#define DAT_0003a18c (0xa95e7UL)
#define DAT_0003a190 (0xa91c0UL)
#define DAT_0003a194 (0x2000a030UL)
#define DAT_0003a198 (0xa9121UL)
#define DAT_0003a19c ((volatile int*)0xf7b6fUL)
#define DAT_0003a514 (0xa9078UL)
#define DAT_0003a518 ((volatile int*)0x20007554UL)
#define DAT_0003a51c (0xa95e7UL)
#define DAT_0003a520 (0xa90deUL)
#define DAT_0003a524 (0xa9100UL)
#define DAT_0003a528 (0x2000a030UL)
#define DAT_0003a52c (0xa8ec6UL)
#define DAT_0003a874 (0xa9121UL)
#define DAT_0003a878 ((volatile int*)0xf7b6fUL)
#define DAT_0003a87c (0xa91f2UL)
#define DAT_0003aba0 ((volatile int*)0x20007554UL)
#define DAT_0003aba4 ((volatile int*)0xa900cUL)
#define DAT_0003aba8 ((volatile int*)0xa9009UL)
#define DAT_0003abac (0xa95e7UL)
#define DAT_0003abb0 (0xa902dUL)
#define DAT_0003abb4 ((volatile int*)0x20004950UL)
#define DAT_0003abb8 (0xa904cUL)
#define DAT_0003abbc (0xa9078UL)
#define DAT_0003abc0 (0xa9082UL)
#define DAT_0003abc4 (0xa909fUL)
#define DAT_0003abc8 (0xf26c1UL)
#define DAT_0003ae58 ((volatile int*)0x20007554UL)
#define DAT_0003ae5c (0xa95e7UL)
#define DAT_0003ae60 (0xa90b7UL)
#define DAT_0003ae64 (0xf26c1UL)
#define DAT_0003ae68 (0xa9078UL)

void DashBoard_Reflash(int param_1,int param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  byte bVar13;
  int iVar14;
  undefined4 *puVar15;
  int iVar16;
  uint uVar17;
  int local_c8;
  uint local_b8;
  uint local_b4;
  undefined4 local_b0;
  uint local_ac;
  undefined4 local_a8;
  char local_a4;
  undefined1 uStack_a3;
  undefined2 uStack_a2;
  char local_a0;
  undefined1 uStack_9f;
  undefined2 uStack_9e;
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 local_94;
  uint local_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 local_80;
  uint local_7c [22];

  piVar2 = DAT_000374c0;
  if (2 < *DAT_000374c0) {
    if (*DAT_000374c4 == 0) {
      log_message(DAT_000374cc,DAT_000374c8,param_4);
    }
    else {
      debug_print(DAT_000374cc,DAT_000374c8,param_4);
    }
  }
  if (param_4 != 1) {
    if (param_4 == 2) {
      iVar4 = ((long long (*)(void))check_charging_and_touch_flags)();
      if (2 < *piVar2) {
        if (*DAT_0003aba0 == 0) {
          uVar5 = DAT_0003aba4;
          if (iVar4 != 1) {
            uVar5 = DAT_0003aba8;
          }
          log_message(DAT_0003abb0,DAT_0003abac,uVar5);
        }
        else {
          uVar5 = DAT_0003aba4;
          if (iVar4 != 1) {
            uVar5 = DAT_0003aba8;
          }
          debug_print(DAT_0003abb0,DAT_0003abac,uVar5);
        }
      }
      iVar9 = DAT_0003abb4;
      if (((*(int *)(DAT_0003abb4 + 0x1c) != iVar4) || (*(char *)(DAT_0003abb4 + 0x19) != '\x02'))
         || (*(char *)(DAT_0003abb4 + 0x1a) != *(char *)(param_1 + 0x65))) {
        ((long long (*)(void))gui_screen_clear)();
        uVar1 = *(undefined1 *)(param_1 + 100);
        *(undefined1 *)(iVar9 + 0x1a) = *(undefined1 *)(param_1 + 0x65);
        iVar14 = *piVar2;
        *(int *)(iVar9 + 0x1c) = iVar4;
        *(undefined1 *)(iVar9 + 0x19) = uVar1;
        if (2 < iVar14) {
          if (*DAT_0003aba0 == 0) {
            log_message(DAT_0003abb8,DAT_0003abac);
          }
          else {
            debug_print(DAT_0003abb8,DAT_0003abac);
          }
        }
      }
      local_94 = 0;
      local_90 = 0;
      local_8c = 0;
      if (iVar4 == 1) {
        uVar5 = ((long long (*)(void))get_timestamp)();
        unix_timestamp_to_datetime(uVar5,&local_94);
        uVar5 = get_localized_weekday_name((char)(local_94 >> 0x10) + '.');
        cVar3 = compute_day_of_week(local_94 & 0xffff,(((local_94)>>16)&0xffff),local_90 & 0xffff);
        uVar6 = get_localized_weekday_name(cVar3 + '(');
        local_80 = 0;
        local_7c[0] = 0;
        local_7c[1] = 0;
        local_7c[2] = 0;
        vdprintf_to_fd(&local_80,0,0x10,DAT_0003abbc,uVar6,uVar5,local_90 & 0xffff);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,&local_80,3,iVar4 + 0x90,iVar9 + 0x1c,iVar14 + 0x104,iVar7 + 0x37,1,0,0,0,0);
        iVar4 = ((long long (*)(void))get_device_info)();
        iVar4 = *(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e) - 1;
        if (iVar4 != 0) {
          iVar4 = 1;
        }
        uVar5 = ((long long (*)(void))get_timestamp)();
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_clock_draw(uVar5,iVar9 + 0xea,iVar14 + 0x4c,iVar7 + 0x180,iVar8 + 0x6d,1,iVar4);
        if (param_3 != 1) {
          return;
        }
        if (2 < *piVar2) {
          if (*DAT_0003aba0 == 0) {
            log_message(DAT_0003abc0,DAT_0003abac,(uint)*(byte *)(param_1 + 4));
          }
          else {
            debug_print(DAT_0003abc0,DAT_0003abac,(uint)*(byte *)(param_1 + 4));
          }
        }
        local_a4 = '\0';
        uStack_a3 = 0;
        uStack_a2 = 0;
        local_a0 = 0;
        uStack_9f = 0;
        uStack_9e = 0;
        if ((byte)(*(char *)(param_1 + 4) - 1U) < 0xfe) {
          uVar5 = ((long long (*)(void))dashboard_reflash_index_lookup)();
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(uVar5,iVar4 + 0x11e,iVar9 + 0x1c,0,0,0);
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar9 = (int)*(char *)(param_1 + 5);
          local_a4 = *(char *)(*(int *)(iVar4 + 0xfec) + 0x5d);
          if (local_a4 == '\0') {
            uStack_a3 = 0;
            uStack_a2 = 0;
            uStack_9f = 0;
            uStack_9e = 0;
            local_a0 = local_a4;
            if (2 < *piVar2) {
              if (*DAT_0003aba0 == 0) {
                log_message(DAT_0003abc4,DAT_0003abac,iVar9);
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            snprintf(&local_a4,8,DAT_0003abc8,iVar9);
            local_b0 = 0;
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_string_draw(3,&local_a4,iVar4 + 0x13a,iVar9 + 0x1c,iVar14 + 0x162,iVar7 + 0x37,
                         &local_b0);
            local_a4 = '*';
          }
          else {
            local_a4 = '\0';
            uStack_a3 = 0;
            uStack_a2 = 0;
            local_a0 = 0;
            uStack_9f = 0;
            uStack_9e = 0;
            iVar4 = (iVar9 * 9) / 5 + 0x20;
            if (2 < *piVar2) {
              if (*DAT_0003ae58 == 0) {
                log_message(DAT_0003ae60,DAT_0003ae5c,iVar4);
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            snprintf(&local_a4,8,DAT_0003ae64,iVar4);
            local_b0 = 0;
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_string_draw(3,&local_a4,iVar4 + 0x13a,iVar9 + 0x1c,iVar14 + 0x162,iVar7 + 0x37,
                         &local_b0);
            local_a4 = '#';
          }
          uStack_9e = 0;
          uStack_9f = 0;
          local_a0 = 0;
          uStack_a2 = 0;
          uStack_a3 = 0;
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = iVar4 + 0x13a + local_b0;
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = local_b0 + iVar9;
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_string_draw(3,&local_a4,iVar7,iVar4 + 0x1c,iVar9 + 0x149,iVar14 + 0x37,0);
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x3c,iVar4 + 0x182,iVar9 + 0x1c,0,0,0);
        ((long long (*)(void))msg_content_recalc_unread)();
        local_a4 = '\0';
        uStack_a3 = 0;
        uStack_a2 = 0;
        local_a0 = 0;
        uStack_9f = 0;
        uStack_9e = 0;
        snprintf(&local_a4,8);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_string_draw(3,&local_a4,iVar4 + 0x19e,iVar9 + 0x1c,iVar14 + 0x1b8,iVar7 + 0x37,0);
        if (*(char *)(param_1 + 0x5f) != '\x01') {
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x1b8,iVar14 + 0x1c,iVar7 + 0x1d0,iVar8 + 0x37);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = iVar9 + 0x1d0;
          iVar4 = iVar4 + 0x1b8;
LAB_0003acba:
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4,iVar7 + 0x1c,iVar9,iVar14 + 0x37);
          return;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar4 = iVar4 + 0x1b8;
      }
      else {
        uVar5 = ((long long (*)(void))get_timestamp)();
        unix_timestamp_to_datetime(uVar5,&local_94);
        uVar5 = get_localized_weekday_name((char)(local_94 >> 0x10) + '.');
        cVar3 = compute_day_of_week(local_94 & 0xffff,(((local_94)>>16)&0xffff),local_90 & 0xffff);
        uVar6 = get_localized_weekday_name(cVar3 + '(');
        local_80 = 0;
        local_7c[0] = 0;
        local_7c[1] = 0;
        local_7c[2] = 0;
        vdprintf_to_fd(&local_80,0,0x10,DAT_0003ae68,uVar6,uVar5,local_90 & 0xffff);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,&local_80,3,iVar4 + 0xb6,iVar9 + 0x1c,iVar14 + 0x12e,iVar7 + 0x37,1,0,0,0,0);
        iVar4 = ((long long (*)(void))get_device_info)();
        iVar4 = *(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e) - 1;
        if (iVar4 != 0) {
          iVar4 = 1;
        }
        uVar5 = ((long long (*)(void))get_timestamp)();
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_clock_draw(uVar5,iVar9 + 0xea,iVar14 + 0x4c,iVar7 + 0x180,iVar8 + 0x6d,1,iVar4);
        if (param_3 != 1) {
          return;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x3e,iVar4 + 0x144,iVar9 + 0x1c,0,0,0);
        if (*(char *)(param_1 + 0x5f) != '\x01') {
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x178,iVar14 + 0x1c,iVar7 + 400,iVar8 + 0x37);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = iVar9 + 400;
          iVar4 = iVar4 + 0x178;
          goto LAB_0003acba;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar4 = iVar4 + 0x178;
      }
      gui_bmp_bitmap_draw(0x42,iVar4,iVar9 + 0x1c,0,0,0);
      return;
    }
    if (param_4 != 0) {
      return;
    }
    iVar4 = ((long long (*)(void))check_charging_and_touch_flags)();
    if (2 < *piVar2) {
      if (*DAT_000374c4 == 0) {
        uVar5 = DAT_000374d0;
        if (iVar4 != 1) {
          uVar5 = DAT_00037918;
        }
        log_message(DAT_00037920,DAT_0003791c,uVar5);
      }
      else {
        uVar5 = DAT_000374d0;
        if (iVar4 != 1) {
          uVar5 = DAT_000374d4;
        }
        debug_print(DAT_000374d8,DAT_000374c8,uVar5);
      }
    }
    iVar9 = DAT_000374dc;
    if (((*(int *)(DAT_000374dc + 0x1c) != iVar4) || (*(char *)(DAT_000374dc + 0x19) != '\0')) ||
       (*(char *)(DAT_000374dc + 0x1a) != *(char *)(param_1 + 0x65))) {
      ((long long (*)(void))gui_screen_clear)();
      uVar1 = *(undefined1 *)(param_1 + 100);
      *(undefined1 *)(iVar9 + 0x1a) = *(undefined1 *)(param_1 + 0x65);
      iVar14 = *piVar2;
      *(int *)(iVar9 + 0x1c) = iVar4;
      *(undefined1 *)(iVar9 + 0x19) = uVar1;
      if (2 < iVar14) {
        if (*DAT_000374c4 == 0) {
          log_message(DAT_000374e0,DAT_000374c8);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
    }
    if (iVar4 == 1) {
      local_b0 = 0;
      local_ac = 0;
      local_a8 = 0;
      uVar5 = ((long long (*)(void))get_timestamp)();
      unix_timestamp_to_datetime(uVar5,&local_b0);
      uVar5 = get_localized_weekday_name((char)(local_b0 >> 0x10) + '.');
      cVar3 = compute_day_of_week(local_b0 & 0xffff,(((local_b0)>>16)&0xffff),local_ac & 0xffff);
      uVar6 = get_localized_weekday_name(cVar3 + '(');
      local_a4 = '\0';
      uStack_a3 = 0;
      uStack_a2 = 0;
      local_a0 = 0;
      uStack_9f = 0;
      uStack_9e = 0;
      local_9c = 0;
      uStack_98 = 0;
      vdprintf_to_fd(&local_a4,0,0x10,DAT_000374e4,uVar6,uVar5,local_ac & 0xffff);
      uVar5 = ((long long (*)(void))device_info_text_width_get)();
      iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,&local_a4,3,uVar5,iVar4 + 2,iVar14 + 0xa0,iVar7 + 0x1d,1,0,0,0,0);
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar4 = *(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e) - 1;
      if (iVar4 != 0) {
        iVar4 = 1;
      }
      uVar5 = ((long long (*)(void))get_timestamp)();
      uVar6 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_clock_draw(uVar5,uVar6,iVar14 + 0x22,iVar7 + 0x96,iVar8 + 0x43,1,iVar4);
      if (param_3 == 1) {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x4f,iVar4 + 0x23e,iVar14 + 4,0,0,0);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x4e,iVar4 + 0xfe,iVar14 + 4,0,0,0);
        if (2 < *piVar2) {
          if (*DAT_00037924 == 0) {
            log_message(DAT_00037928,DAT_0003791c,(uint)*(byte *)(param_1 + 4));
          }
          else {
            ((long long (*)(void))debug_print)();
          }
        }
        local_b8 = 0;
        local_b4 = 0;
        if ((byte)(*(char *)(param_1 + 4) - 1U) < 0xfe) {
          uVar5 = ((long long (*)(void))dashboard_reflash_index_lookup)();
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(uVar5,iVar4 + 0xa0,iVar14 + 1,0,0,0);
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar14 = (int)*(char *)(param_1 + 5);
          local_b8 = (uint)*(byte *)(*(int *)(iVar4 + 0xfec) + 0x5d);
          if (local_b8 == 0) {
            local_b4 = local_b8;
            if (2 < *piVar2) {
              if (*DAT_00037924 == 0) {
                log_message(DAT_0003792c,DAT_0003791c,iVar14);
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            snprintf(&local_b8,8,DAT_00037930,iVar14);
            local_80 = 0;
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_string_draw(3,&local_b8,iVar4 + 0xbc,iVar14 + 1,iVar7 + 0xf8,iVar8 + 0x1c,&local_80);
            bVar13 = 0x2a;
          }
          else {
            local_b8 = 0;
            local_b4 = 0;
            iVar4 = (iVar14 * 9) / 5 + 0x20;
            if (2 < *piVar2) {
              if (*DAT_00037c0c == 0) {
                log_message(DAT_00037c14,DAT_00037c10,iVar4);
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            snprintf(&local_b8,8,DAT_00037c18,iVar4);
            local_80 = 0;
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_string_draw(3,&local_b8,iVar4 + 0xbc,iVar14 + 1,iVar7 + 0xf8,iVar8 + 0x1c,&local_80);
            bVar13 = 0x23;
          }
          local_b4 = 0;
          local_b8 = (uint)bVar13;
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = local_80 + iVar4;
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = local_80 + iVar7;
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_string_draw(3,&local_b8,iVar4 + 0xbe,iVar14 + 1,iVar7 + 0xcb,iVar8 + 0x1c,0);
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x3c,iVar4 + 0xa0,iVar14 + 0x25,0,0,0);
        ((long long (*)(void))msg_content_recalc_unread)();
        local_b8 = 0;
        local_b4 = 0;
        snprintf(&local_b8,8);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_string_draw(3,&local_b8,iVar4 + 0xbc,iVar14 + 0x25,iVar7 + 0xe8,iVar8 + 0x40,0);
        if (*(char *)(param_1 + 0x5f) == '\x01') {
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(0x42,iVar4 + 0xdc,iVar14 + 0x25,0,0,0);
        }
        else {
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0xdc,iVar7 + 0x25,iVar8 + 0xf4,iVar12 + 0x40);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xdc,iVar14 + 0x25,iVar7 + 0xf4,iVar8 + 0x40);
        }
        uVar5 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x39,uVar5,iVar4 + 0x56,0,0,0);
        if (*(char *)(iVar9 + 0x20) != *(char *)(param_1 + 0x66)) {
          *(char *)(iVar9 + 0x20) = *(char *)(param_1 + 0x66);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_area_clear(iVar4 + 0x1c,iVar14 + 0x51,iVar7 + 0xf2,iVar8 + 0x6c);
          uVar5 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_area_clear(uVar5,iVar4 + 0x6c,iVar14 + 0xf2,iVar7 + 0x87);
        }
        cVar3 = *(char *)(iVar9 + 0x20);
        if (cVar3 == '\0') {
          iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
          local_80 = *DAT_00037938;
          local_7c[0] = DAT_00037938[1];
          local_94 = *DAT_0003793c;
          local_90 = CONCAT22((((local_90)>>16)&0xffff),*(undefined2 *)(DAT_0003793c + 1));
          puVar10 = &local_80;
          if (iVar4 == 6) {
            puVar10 = &local_94;
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_area_clear(iVar4 + 0x1c,iVar14 + 0x51,iVar7 + 0xf2,iVar8 + 0x6c);
          uVar5 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar4 = iVar4 + 0x6c;
          iVar7 = iVar7 + 0x89;
          iVar14 = iVar14 + 0xf2;
        }
        else {
          if (cVar3 == '\x01') {
            iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
            puVar10 = &local_94;
            puVar15 = DAT_00037c1c;
            do {
              uVar5 = *puVar15;
              uVar6 = puVar15[1];
              puVar15 = puVar15 + 2;
              *puVar10 = uVar5;
              puVar10[1] = uVar6;
              puVar10 = puVar10 + 2;
            } while (puVar15 != DAT_00037c1c + 4);
            puVar11 = &local_80;
            *(undefined1 *)puVar10 = *(undefined1 *)puVar15;
            puVar10 = DAT_00037c20;
            do {
              uVar5 = *puVar10;
              uVar6 = puVar10[1];
              puVar10 = puVar10 + 2;
              *puVar11 = uVar5;
              puVar11[1] = uVar6;
              puVar11 = puVar11 + 2;
            } while (puVar10 != DAT_00037c20 + 6);
          }
          else {
            if (cVar3 != '\x02') {
              if (cVar3 != '\x03') goto LAB_0003741a;
              iVar4 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_utf_draw(0,DAT_00037c2c,0,iVar4 + 0x1c,iVar14 + 0x51,iVar7 + 0xf2,iVar8 + 0x6c,1,0
                           ,0,0,0);
              local_80 = 0;
              memset_bytes(local_7c,0,0x54);
              uVar5 = strlen(DAT_00037c30);
              safe_memcpy_checked(&local_80,DAT_00037c30,uVar5,0x58);
              iVar4 = strlen(DAT_00037c30);
              *(undefined1 *)((int)local_7c + iVar4 + -4) = 0x20;
              uVar5 = strlen(DAT_00037c34);
              memcpy((int)local_7c + iVar4 + -3,DAT_00037c34,uVar5);
              uVar5 = ((long long (*)(void))device_info_text_width_get)();
              iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = iVar14 + 0xf2;
              iVar4 = iVar4 + 0x6c;
              iVar7 = iVar7 + 0x87;
              puVar10 = &local_80;
              goto LAB_00037904;
            }
            iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
            puVar10 = &local_94;
            puVar15 = DAT_00037c24;
            do {
              uVar5 = *puVar15;
              uVar6 = puVar15[1];
              puVar15 = puVar15 + 2;
              *puVar10 = uVar5;
              puVar10[1] = uVar6;
              puVar10 = puVar10 + 2;
            } while (puVar15 != DAT_00037c24 + 4);
            puVar11 = &local_80;
            *(undefined2 *)puVar10 = *(undefined2 *)puVar15;
            puVar10 = DAT_00037c28;
            do {
              uVar5 = *puVar10;
              uVar6 = puVar10[1];
              puVar10 = puVar10 + 2;
              *puVar11 = uVar5;
              puVar11[1] = uVar6;
              puVar11 = puVar11 + 2;
            } while (puVar10 != DAT_00037c28 + 6);
          }
          puVar10 = &local_94;
          if (iVar4 == 6) {
            puVar10 = &local_80;
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_area_clear(iVar4 + 0x1c,iVar14 + 0x51,iVar7 + 0xf2,iVar8 + 0x6c);
          uVar5 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = iVar7 + 0x89;
          iVar4 = iVar4 + 0x6e;
          iVar14 = iVar14 + 0xf2;
        }
LAB_00037904:
        gui_utf_draw(0,puVar10,0,uVar5,iVar4,iVar14,iVar7,1,0,0,0,0);
      }
      else if (param_3 != 4) {
        return;
      }
LAB_0003741a:
      iVar4 = DAT_00037eb8;
      uVar17 = (uint)*(byte *)(iVar9 + 0x1a);
      if (uVar17 != 0) {
        if (uVar17 == 1) {
          iVar14 = 0;
          iVar7 = 0;
          do {
            iVar8 = iVar14 * 0x7f2;
            iVar14 = iVar14 + 1;
            if (*(char *)(DAT_00037eb8 + iVar8) == '\x01') {
              iVar7 = iVar7 + 1;
            }
          } while (iVar14 != 4);
          cVar3 = *(char *)(param_1 + 0x68);
          if (cVar3 != '\0') {
            if (cVar3 == '\x01') {
              if (*(char *)(iVar9 + 0x21) != '\x01') {
                *(undefined1 *)(iVar9 + 0x21) = 1;
                iVar4 = ((long long (*)(void))device_info_text_width_get)();
                uVar5 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar9 = ((long long (*)(void))device_info_text_width_get)();
                iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
                gui_area_clear(iVar4 + 0x100,uVar5,iVar9 + 0x23c,iVar14 + 0x88);
              }
              if (2 < *piVar2) {
                if (*DAT_00038268 == 0) {
                  log_message(DAT_00038270,DAT_0003826c,(uint)*(byte *)(param_1 + 0x68));
                }
                else {
                  ((long long (*)(void))debug_print)();
                }
              }
              if (iVar7 == 0) {
                ((long long (*)(void))cleanStocksIndex)();
              }
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
              uVar5 = 0x43;
              goto LAB_00037f2e;
            }
            if (cVar3 != '\x02') {
              return;
            }
            if (*(char *)(iVar9 + 0x21) != '\x02') {
              *(undefined1 *)(iVar9 + 0x21) = 2;
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar8 = ((long long (*)(void))device_info_text_width_get)();
              iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_area_clear(iVar14 + 0x100,iVar7 + 4,iVar8 + 0x23c,iVar12 + 0x88);
            }
            iVar14 = 0;
            iVar7 = 0;
            do {
              iVar8 = iVar14 * 0x7f2;
              iVar14 = iVar14 + 1;
              if (*(char *)(iVar4 + iVar8) == '\x01') {
                iVar7 = iVar7 + 1;
              }
            } while (iVar14 != 4);
            uVar17 = (uint)*(byte *)(iVar9 + 3);
            *(char *)(iVar9 + 4) = (char)iVar7;
            cVar3 = *(char *)(uVar17 * 0x7f2 + iVar4 + 1);
            if (cVar3 == '\0') {
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = iVar14 + 2;
              uVar5 = 0x46;
              iVar9 = iVar9 + 0x10a;
LAB_0003803a:
              gui_bmp_bitmap_draw(uVar5,iVar9,iVar14,0,0,0);
            }
            else {
              if (cVar3 == '\x01') {
                iVar9 = ((long long (*)(void))device_info_text_width_get)();
                iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar14 = iVar14 + 2;
                uVar5 = 0x44;
                iVar9 = iVar9 + 0x10a;
                goto LAB_0003803a;
              }
              if (cVar3 == '\x02') {
                iVar9 = ((long long (*)(void))device_info_text_width_get)();
                iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar14 = iVar14 + 2;
                uVar5 = 0x45;
                iVar9 = iVar9 + 0x10a;
                goto LAB_0003803a;
              }
            }
            if (iVar7 == 0) {
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_area_clear(iVar9 + 0x218,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c);
            }
            else {
              local_80 = 0;
              memset_bytes(local_7c,0,0x1c);
              snprintf(&local_80,0x20,DAT_0003827c,uVar17 + 1,iVar7);
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_utf_draw(0,&local_80,0,iVar9 + 0x218,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c,1,0,0,0
                           ,0);
            }
            iVar12 = uVar17 * 0x7f2;
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            uVar5 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw(0,iVar12 + 4 + iVar4,0,iVar9 + 0x126,uVar5,iVar14 + 0x200,iVar7 + 0x1b,1,0,
                         0,0,0);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw(0,iVar12 + 0x24 + iVar4,0,iVar9 + 0x10a,iVar14 + 0x1b,iVar7 + 0x232,
                         iVar8 + 0x36,1,0,0,0,0);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw_align_right(0,iVar12 + 100 + iVar4,0,iVar9 + 0x1d2,iVar14 + 0x36,iVar7 + 0x232,
                         iVar8 + 0x51,1,0,0,0,0);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw_align_right(0,iVar12 + 0x74 + iVar4,0,iVar9 + 0x1d2,iVar14 + 0x51,iVar7 + 0x232,
                         iVar8 + 0x6c,1,0,0,0,0);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw_align_right(0,iVar12 + 0x84 + iVar4,0,iVar9 + 0x1d2,iVar14 + 0x6c,iVar7 + 0x232,
                         iVar8 + 0x87,1,0,0,0,0);
            iVar8 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar4 = iVar12 + 0x94 + iVar4;
            iVar9 = iVar9 + 0x1c2;
            iVar8 = iVar8 + 0x10a;
            goto LAB_00038220;
          }
          if (2 < *piVar2) {
            if (*DAT_00037ea4 == 0) {
              log_message(DAT_00037eac,DAT_00037ea8,0);
            }
            else {
              debug_print(DAT_00037eac,DAT_00037ea8,0);
            }
          }
          if (*(char *)(iVar9 + 0x21) != *(char *)(param_1 + 0x68)) {
            *(char *)(iVar9 + 0x21) = *(char *)(param_1 + 0x68);
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_area_clear(iVar4 + 0x100,iVar9 + 4,iVar14 + 0x23c,iVar8 + 0x88);
          }
          if (iVar7 == 0) {
            ((long long (*)(void))cleanStocksIndex)();
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(0x43,iVar4 + 0x10a,iVar9 + 2,0,0,0);
          iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
          if (iVar4 == 6) {
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = iVar7 + 0x51;
            iVar14 = iVar14 + 0x236;
            iVar4 = iVar4 + 0x36;
            iVar9 = iVar9 + 0x182;
            uVar5 = DAT_00037eb4;
            goto LAB_00037e92;
          }
        }
        else {
          if (uVar17 != 2) {
            return;
          }
          iVar14 = 0;
          local_80 = 0;
          iVar7 = 0;
          memset_bytes(local_7c,0,0x1c);
          iVar4 = DAT_0003861c;
          do {
            if (*(char *)(iVar4 + iVar14 * 0x159) == '\x01') {
              if (2 < *piVar2) {
                if (*DAT_00038600 == 0) {
                  log_message(DAT_00038608,DAT_00038604,iVar14);
                }
                else {
                  ((long long (*)(void))debug_print)();
                }
              }
              iVar7 = iVar7 + 1;
            }
            iVar14 = iVar14 + 1;
          } while (iVar14 != 4);
          cVar3 = *(char *)(param_1 + 0x69);
          if (cVar3 != '\0') {
            if (cVar3 != '\x01') {
              if (cVar3 != '\x02') {
                return;
              }
              if (*(char *)(iVar9 + 0x22) != '\x02') {
                *(undefined1 *)(iVar9 + 0x22) = 2;
                iVar14 = ((long long (*)(void))device_info_text_width_get)();
                uVar5 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar8 = ((long long (*)(void))device_info_text_width_get)();
                iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
                gui_area_clear(iVar14 + 0x100,uVar5,iVar8 + 0x23c,iVar12 + 0x88);
              }
              if (2 < *piVar2) {
                if (*DAT_00038600 == 0) {
                  log_message(DAT_00038614,DAT_00038604,iVar7);
                }
                else {
                  ((long long (*)(void))debug_print)();
                }
              }
              *(char *)(iVar9 + 6) = (char)iVar7;
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_bmp_bitmap_draw(0x47,iVar14 + 0x10a,iVar8 + 2,0,0,0);
              if (iVar7 != 0) {
                *(undefined1 *)(iVar9 + 8) = 1;
                memset_bytes(&local_80,0,0x20);
                snprintf(&local_80,0x20,DAT_00038748,*(byte *)(iVar9 + 5) + 1,iVar7);
                iVar9 = (uint)*(byte *)(iVar9 + 5) * 0x159;
                iVar14 = ((long long (*)(void))device_info_text_width_get)();
                iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar12 = ((long long (*)(void))device_info_text_width_get)();
                iVar16 = ((long long (*)(void))device_info_text_height_get_clamped)();
                gui_utf_draw(0,iVar9 + 1 + iVar4,0,iVar14 + 0x128,iVar8 + 1,iVar12 + 0x212,
                             iVar16 + 0x1c,1,0,0,0,0);
                if (iVar7 == 1) {
                  iVar14 = ((long long (*)(void))device_info_text_width_get)();
                  iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
                  iVar8 = ((long long (*)(void))device_info_text_width_get)();
                  iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
                  puVar10 = DAT_0003874c;
                }
                else {
                  iVar14 = ((long long (*)(void))device_info_text_width_get)();
                  iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
                  iVar8 = ((long long (*)(void))device_info_text_width_get)();
                  iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
                  puVar10 = &local_80;
                }
                gui_utf_draw(0,puVar10,0,iVar14 + 0x218,iVar12 + 1,iVar8 + 0x23a,iVar7 + 0x1c,1,0,0,
                             0,0);
                iVar14 = ((long long (*)(void))device_info_text_width_get)();
                iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar7 = ((long long (*)(void))device_info_text_width_get)();
                iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar7 = iVar7 + 0x238;
                iVar14 = iVar14 + 0x10a;
                goto LAB_00038708;
              }
              iVar4 = dashboard_read_word(DAT_00038618);
              if ((-1 < iVar4 << 0x1e) || (*(char *)(iVar9 + 8) != '\x01')) goto LAB_000385f0;
              *(char *)(iVar9 + 8) = (char)iVar7;
              iVar4 = ((long long (*)(void))get_device_info)();
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x128,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c);
              iVar4 = ((long long (*)(void))get_device_info)();
              uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
              iVar4 = ((long long (*)(void))get_device_info)();
              uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
              iVar4 = ((long long (*)(void))device_info_text_width_get)();
              iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
              reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x128,iVar9 + 1,iVar14 + 0x23a,iVar7 + 0x1c);
              iVar4 = ((long long (*)(void))get_device_info)();
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x10a,iVar14 + 0x1c,iVar7 + 0x232,iVar8 + 0x88);
              iVar4 = ((long long (*)(void))get_device_info)();
              uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
              iVar4 = ((long long (*)(void))get_device_info)();
              uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
              iVar4 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar9 = iVar9 + 0x232;
              iVar4 = iVar4 + 0x10a;
              goto LAB_000385e8;
            }
            if (*(char *)(iVar9 + 0x22) != '\x01') {
              *(undefined1 *)(iVar9 + 0x22) = 1;
              iVar4 = ((long long (*)(void))device_info_text_width_get)();
              uVar5 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_area_clear(iVar4 + 0x100,uVar5,iVar9 + 0x23c,iVar14 + 0x88);
            }
            if (iVar7 == 0) {
              ((long long (*)(void))cleanNewsIndex)();
            }
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            uVar5 = 0x47;
LAB_00037f2e:
            gui_bmp_bitmap_draw(uVar5,iVar9 + 0x10a,iVar4 + 2,0,0,0);
            iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
            if (iVar4 == 6) {
              iVar4 = ((long long (*)(void))device_info_text_width_get)();
              iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_utf_draw(0,DAT_0003860c,0,iVar4 + 0x130,iVar9 + 0x2a,iVar14 + 0x236,iVar7 + 0x45,1
                           ,0,0,0,0);
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar9 = iVar9 + 0x15a;
LAB_0003846c:
              iVar7 = iVar7 + 0x60;
              iVar14 = iVar14 + 0x236;
              iVar4 = iVar4 + 0x45;
              uVar5 = DAT_00038610;
              goto LAB_00037e92;
            }
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw(0,DAT_00038274,0,iVar4 + 0x152,iVar9 + 0x2a,iVar14 + 0x236,iVar7 + 0x45,1,0
                         ,0,0,0);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar9 = iVar9 + 0x152;
            goto LAB_00037fac;
          }
          if (*(char *)(iVar9 + 0x22) != '\0') {
            *(undefined1 *)(iVar9 + 0x22) = 0;
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_area_clear(iVar4 + 0x100,iVar9 + 4,iVar14 + 0x23c,iVar8 + 0x88);
          }
          if (iVar7 == 0) {
            ((long long (*)(void))cleanNewsIndex)();
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(0x47,iVar4 + 0x10a,iVar9 + 2,0,0,0);
          iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
          if (iVar4 == 6) {
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = iVar7 + 0x51;
            iVar14 = iVar14 + 0x236;
            iVar4 = iVar4 + 0x36;
            iVar9 = iVar9 + 0x17a;
            uVar5 = DAT_00037eb4;
            goto LAB_00037e92;
          }
        }
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar9 = iVar9 + 0x17a;
        goto LAB_00037e4a;
      }
      local_80 = uVar17;
      memset_bytes(local_7c,0,0x1c);
      iVar4 = 0;
      iVar14 = 0;
      do {
        if (*(char *)(iVar4 * 0x143 + *(int *)(param_2 + 0x1020) + 3) == '\x01') {
          if (2 < *piVar2) {
            if (*DAT_000374c4 == 0) {
              log_message(DAT_000374e8,DAT_000374c8,iVar4);
            }
            else {
              ((long long (*)(void))debug_print)();
            }
          }
          iVar14 = iVar14 + 1;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      if (2 < *piVar2) {
        if (*DAT_000374c4 == 0) {
          log_message(DAT_000374ec,DAT_000374c8,iVar14);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      *(char *)(iVar9 + 2) = (char)iVar14;
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x3b,iVar4 + 0x10a,iVar7 + 2,0,0,0);
      if (iVar14 == 0) {
        iVar4 = dashboard_read_word(DAT_000374f0);
        if ((iVar4 << 0x1e < 0) && (*(char *)(iVar9 + 7) == '\x01')) {
          *(char *)(iVar9 + 7) = (char)iVar14;
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x128,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x128,iVar9 + 1,iVar14 + 0x23a,iVar7 + 0x1c);
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x10a,iVar14 + 0x1c,iVar7 + 0x232,iVar8 + 0x88);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x10a,iVar9 + 0x1c,iVar14 + 0x232,iVar7 + 0x88);
        }
        ((long long (*)(void))reset_touch_selection_state)();
        ((long long (*)(void))draw_quicknote_hint_on_dashboard)();
        return;
      }
      *(undefined1 *)(iVar9 + 7) = 1;
      memset_bytes(&local_80,0,0x20);
      snprintf(&local_80,0x20,DAT_00037e9c,*(byte *)(iVar9 + 1) + 1,iVar14);
      iVar12 = *(int *)(param_2 + 0x1020);
      iVar16 = (uint)*(byte *)(iVar9 + 1) * 0x143;
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,iVar12 + iVar16 + 4,0,iVar4 + 0x128,iVar9 + 1,iVar7 + 0x212,iVar8 + 0x1c,1,0,0,
                   0,0);
      if (iVar14 == 1) {
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        puVar10 = DAT_00037ea0;
      }
      else {
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        puVar10 = &local_80;
      }
      gui_utf_draw(0,puVar10,0,iVar7 + 0x218,iVar14 + 1,iVar9 + 0x23a,iVar4 + 0x1c,1,0,0,0,0);
      iVar4 = iVar16 + 0x2d + *(int *)(param_2 + 0x1020);
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = iVar7 + 0x238;
      iVar14 = iVar14 + 0x10a;
    }
    else {
      local_a4 = '\0';
      uStack_a3 = 0;
      uStack_a2 = 0;
      local_a0 = 0;
      uStack_9f = 0;
      uStack_9e = 0;
      local_9c = 0;
      uVar5 = ((long long (*)(void))get_timestamp)();
      unix_timestamp_to_datetime(uVar5,&local_a4);
      uVar5 = get_localized_weekday_name((char)uStack_a2 + '.');
      cVar3 = compute_day_of_week(CONCAT11(uStack_a3,local_a4),uStack_a2,CONCAT11(uStack_9f,local_a0));
      uVar6 = get_localized_weekday_name(cVar3 + '(');
      local_94 = 0;
      local_90 = 0;
      local_8c = 0;
      uStack_88 = 0;
      vdprintf_to_fd(&local_94,0,0x10,DAT_00038adc,uVar6,uVar5,CONCAT11(uStack_9f,local_a0));
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      uVar5 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,&local_94,3,iVar4 + 0x2e,uVar5,iVar14 + 0xcd,iVar7 + 0x1b,1,0,0,0,0);
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar4 = *(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e) - 1;
      if (iVar4 != 0) {
        iVar4 = 1;
      }
      uVar5 = ((long long (*)(void))get_timestamp)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_clock_draw(uVar5,iVar14 + 0x2e,iVar7 + 0x34,iVar8 + 0xc3,iVar12 + 0x55,1,iVar4);
      if (param_3 == 1) {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x3e,iVar4 + 0x2e,iVar14 + 0x6d,0,0,0);
        if (*(char *)(param_1 + 0x5f) == '\x01') {
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(0x42,iVar4 + 0x8e,iVar14 + 0x6d,0,0,0);
        }
        else {
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0x8e,iVar7 + 0x6d,iVar8 + 0xa6,iVar12 + 0x88);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x8e,iVar14 + 0x6d,iVar7 + 0xa6,iVar8 + 0x88);
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x4f,iVar4 + 0x214,iVar14 + 4,0,0,0);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x4e,iVar4 + 0xd4,iVar14 + 4,0,0,0);
      }
      else if (param_3 != 4) {
        return;
      }
      uVar17 = (uint)*(byte *)(iVar9 + 0x1a);
      if (uVar17 != 0) {
        if (uVar17 == 1) {
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(0x43,iVar4 + 0x10a,iVar9 + 2,0,0,0);
          iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
          if (iVar4 != 6) {
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = iVar7 + 0x51;
            iVar14 = iVar14 + 0x208;
            iVar4 = iVar4 + 0x36;
            iVar9 = iVar9 + 0x106;
            uVar5 = DAT_00038f58;
            goto LAB_00037e92;
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,DAT_00038f5c,0,iVar4 + 0x116,iVar9 + 0x31,iVar14 + 0x208,iVar7 + 0x4c,1,0,0
                       ,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        }
        else {
          if (uVar17 != 2) {
            return;
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_bmp_bitmap_draw(0x47,iVar4 + 0x10a,iVar9 + 2,0,0,0);
          iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
          if (iVar4 != 6) {
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = iVar7 + 0x51;
            iVar14 = iVar14 + 0x208;
            iVar4 = iVar4 + 0x36;
            iVar9 = iVar9 + 0x106;
            uVar5 = DAT_00038f58;
            goto LAB_00037e92;
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,DAT_00038f5c,0,iVar4 + 0x116,iVar9 + 0x31,iVar14 + 0x208,iVar7 + 0x4c,1,0,0
                       ,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        }
        iVar14 = iVar14 + 0x208;
        iVar9 = iVar9 + 0x11e;
        goto LAB_00038e72;
      }
      local_80 = uVar17;
      memset_bytes(local_7c,0,0x1c);
      iVar4 = 0;
      iVar14 = 0;
      do {
        if (*(char *)(iVar4 * 0x143 + *(int *)(param_2 + 0x1020) + 3) == '\x01') {
          if (2 < *piVar2) {
            if (*DAT_00038ae0 == 0) {
              log_message(DAT_00038ae8,DAT_00038ae4,iVar4);
            }
            else {
              ((long long (*)(void))debug_print)();
            }
          }
          iVar14 = iVar14 + 1;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      if (2 < *piVar2) {
        if (*DAT_00038ae0 == 0) {
          log_message(DAT_00038aec,DAT_00038ae4,iVar14);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      *(char *)(iVar9 + 2) = (char)iVar14;
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x3b,iVar4 + 0xe0,iVar7 + 2,0,0,0);
      if (iVar14 == 0) {
        iVar4 = dashboard_read_word(DAT_00038af0);
        if ((iVar4 << 0x1e < 0) && (*(char *)(iVar9 + 7) == '\x01')) {
          *(char *)(iVar9 + 7) = (char)iVar14;
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0x128,iVar7 + 1,iVar8 + 0x208,iVar12 + 0x1c);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x128,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c);
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0x10a,iVar7 + 0x1c,iVar8 + 0x208,iVar12 + 0x88);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x10a,iVar14 + 0x1c,iVar7 + 0x208,iVar8 + 0x88);
        }
        ((long long (*)(void))reset_touch_selection_state)();
        uVar17 = ((long long (*)(void))get_ui_mode_flag_byte1)();
        if (*(byte *)(iVar9 + 0x18) != uVar17) {
          *(char *)(iVar9 + 0x18) = (char)uVar17;
          iVar4 = ((long long (*)(void))get_device_info)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0x10a,iVar14 + 0x1c,iVar7 + 0x232,iVar8 + 0x88);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
          iVar4 = ((long long (*)(void))get_device_info)();
          uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x10a,iVar9 + 0x1c,iVar14 + 0x232,iVar7 + 0x88);
        }
        if (uVar17 == 6) {
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,DAT_00038f4c,0,iVar4 + 0x108,iVar9 + 0x28,iVar14 + 0x1e4,iVar7 + 0x43,1,0,0
                       ,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = iVar14 + 0x20c;
          goto LAB_00038c66;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,DAT_00038af4,0,iVar4 + 0x118,iVar9 + 0x28,iVar14 + 0x1e0,iVar7 + 0x43,1,0,0,0
                     ,0);
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = iVar14 + 0x1da;
        iVar9 = iVar9 + 0x126;
LAB_00038ad4:
        iVar7 = iVar7 + 0x5e;
        iVar4 = iVar4 + 0x43;
        uVar5 = DAT_00038af8;
        goto LAB_00037e92;
      }
      *(undefined1 *)(iVar9 + 7) = 1;
      memset_bytes(&local_80,0,0x20);
      snprintf(&local_80,0x20,DAT_00038f50,*(byte *)(iVar9 + 1) + 1,iVar14);
      iVar12 = *(int *)(param_2 + 0x1020);
      iVar16 = (uint)*(byte *)(iVar9 + 1) * 0x143;
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,iVar12 + iVar16 + 4,0,iVar4 + 0xfc,iVar9 + 1,iVar7 + 0x1d6,iVar8 + 0x1c,1,0,0,0
                   ,0);
      if (iVar14 == 1) {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        puVar10 = DAT_00038f54;
      }
      else {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        puVar10 = &local_80;
      }
      gui_utf_draw(0,puVar10,0,iVar4 + 0x1e4,iVar9 + 1,iVar14 + 0x212,iVar7 + 0x1c,1,0,0,0,0);
      iVar4 = iVar16 + 0x2d + *(int *)(param_2 + 0x1020);
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = iVar7 + 0x208;
      iVar14 = iVar14 + 0xe0;
    }
    iVar12 = iVar12 + 0x88;
    iVar8 = iVar8 + 0x1c;
LAB_00037d2a:
    gui_utf_draw_dark_light_split(0,iVar4,0,iVar14,iVar8,iVar7,iVar12,4,0x200b,0,0,0);
    return;
  }
  iVar4 = ((long long (*)(void))check_charging_and_touch_flags)();
  if (2 < *piVar2) {
    if (*DAT_0003925c == 0) {
      uVar5 = DAT_00039260;
      if (iVar4 != 1) {
        uVar5 = DAT_00039618;
      }
      log_message(DAT_00039620,DAT_0003961c,uVar5);
    }
    else {
      uVar5 = DAT_00039260;
      if (iVar4 != 1) {
        uVar5 = DAT_00039264;
      }
      debug_print(DAT_0003926c,DAT_00039268,uVar5);
    }
  }
  iVar9 = DAT_00039270;
  if (((*(int *)(DAT_00039270 + 0x1c) != iVar4) || (*(char *)(DAT_00039270 + 0x19) != '\x01')) ||
     (*(char *)(DAT_00039270 + 0x1a) != *(char *)(param_1 + 0x65))) {
    ((long long (*)(void))gui_screen_clear)();
    uVar1 = *(undefined1 *)(param_1 + 100);
    *(undefined1 *)(iVar9 + 0x1a) = *(undefined1 *)(param_1 + 0x65);
    iVar14 = *piVar2;
    *(int *)(iVar9 + 0x1c) = iVar4;
    *(undefined1 *)(iVar9 + 0x19) = uVar1;
    if (2 < iVar14) {
      if (*DAT_0003925c == 0) {
        log_message(DAT_00039274,DAT_00039268);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
  }
  local_a4 = '\0';
  uStack_a3 = 0;
  uStack_a2 = 0;
  local_a0 = 0;
  uStack_9f = 0;
  uStack_9e = 0;
  local_9c = 0;
  if (iVar4 == 1) {
    uVar5 = ((long long (*)(void))get_timestamp)();
    unix_timestamp_to_datetime(uVar5,&local_a4);
    uVar5 = get_localized_weekday_name((char)uStack_a2 + '.');
    cVar3 = compute_day_of_week(CONCAT11(uStack_a3,local_a4),uStack_a2,CONCAT11(uStack_9f,local_a0));
    uVar6 = get_localized_weekday_name(cVar3 + '(');
    local_94 = 0;
    local_90 = 0;
    local_8c = 0;
    uStack_88 = 0;
    vdprintf_to_fd(&local_94,0,0x10,DAT_00039278,uVar6,uVar5,CONCAT11(uStack_9f,local_a0));
    uVar5 = ((long long (*)(void))device_info_text_width_get)();
    iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_utf_draw(0,&local_94,3,uVar5,iVar4 + 2,iVar14 + 0x88,iVar7 + 0x1d,1,0,0,0,0);
    iVar4 = ((long long (*)(void))get_device_info)();
    iVar4 = *(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e) - 1;
    if (iVar4 != 0) {
      iVar4 = 1;
    }
    uVar5 = ((long long (*)(void))get_timestamp)();
    uVar6 = ((long long (*)(void))device_info_text_width_get)();
    iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar7 = ((long long (*)(void))device_info_text_width_get)();
    iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_clock_draw(uVar5,uVar6,iVar14 + 0x34,iVar7 + 0x96,iVar8 + 0x55,1,iVar4);
    if (param_3 == 1) {
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x4f,iVar4 + 0x240,iVar14 + 4,0,0,0);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x4e,iVar4 + 0xac,iVar14 + 4,0,0,0);
      if (2 < *piVar2) {
        if (*DAT_00039624 == 0) {
          log_message(DAT_00039628,DAT_0003961c,(uint)*(byte *)(param_1 + 4));
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      local_80 = 0;
      local_7c[0] = 0;
      if ((byte)(*(char *)(param_1 + 4) - 1U) < 0xfe) {
        uVar5 = ((long long (*)(void))dashboard_reflash_index_lookup)();
        uVar6 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(uVar5,uVar6,iVar4 + 0x6d,0,0,0);
        iVar4 = ((long long (*)(void))get_device_info)();
        iVar14 = (int)*(char *)(param_1 + 5);
        local_80 = (uint)*(byte *)(*(int *)(iVar4 + 0xfec) + 0x5d);
        if (local_80 == 0) {
          local_7c[0] = local_80;
          if (2 < *piVar2) {
            if (*DAT_00039624 == 0) {
              log_message(DAT_0003962c,DAT_0003961c,iVar14);
            }
            else {
              ((long long (*)(void))debug_print)();
            }
          }
          snprintf(&local_80,8,DAT_00039630,iVar14);
          local_b0 = 0;
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_string_draw(3,&local_80,iVar4 + 0x1c,iVar14 + 0x6d,iVar7 + 0x58,iVar8 + 0x88,&local_b0);
          bVar13 = 0x2a;
        }
        else {
          local_80 = 0;
          local_7c[0] = 0;
          iVar4 = (iVar14 * 9) / 5 + 0x20;
          if (2 < *piVar2) {
            if (*DAT_00039624 == 0) {
              log_message(DAT_00039638,DAT_0003961c,iVar4);
            }
            else {
              ((long long (*)(void))debug_print)();
            }
          }
          snprintf(&local_80,8,DAT_00039630,iVar4);
          local_b0 = 0;
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_string_draw(3,&local_80,iVar4 + 0x1c,iVar14 + 0x6d,iVar7 + 0x58,iVar8 + 0x88,&local_b0);
          bVar13 = 0x23;
        }
        local_7c[0] = 0;
        local_80 = (uint)bVar13;
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = iVar4 + 0x1c + local_b0;
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = local_b0 + iVar14;
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_string_draw(3,&local_80,iVar8,iVar4 + 0x6d,iVar14 + 0x67,iVar7 + 0x88,0);
      }
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x3c,iVar4 + 0x60,iVar14 + 0x6d,0,0,0);
      ((long long (*)(void))msg_content_recalc_unread)();
      local_80 = 0;
      local_7c[0] = 0;
      snprintf(&local_80,8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_string_draw(3,&local_80,iVar4 + 0x7c,iVar14 + 0x6d,iVar7 + 0x9a,iVar8 + 0x88,0);
      if (*(char *)(param_1 + 0x5f) == '\x01') {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x42,iVar4 + 0x8c,iVar14 + 1,0,0,0);
      }
      else {
        iVar4 = ((long long (*)(void))get_device_info)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar8 = ((long long (*)(void))device_info_text_width_get)();
        iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
        clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0x8c,iVar7 + 1,iVar8 + 0xa4,iVar12 + 0x1c);
        iVar4 = ((long long (*)(void))get_device_info)();
        uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
        iVar4 = ((long long (*)(void))get_device_info)();
        uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x8c,iVar14 + 1,iVar7 + 0xa4,iVar8 + 0x1c);
      }
    }
    else if (param_3 != 4) {
      return;
    }
    iVar4 = DAT_00039a30;
    uVar17 = (uint)*(byte *)(iVar9 + 0x1a);
    if (uVar17 != 0) {
      if (uVar17 == 1) {
        iVar14 = 0;
        iVar7 = 0;
        do {
          iVar8 = iVar14 * 0x7f2;
          iVar14 = iVar14 + 1;
          if (*(char *)(DAT_00039a30 + iVar8) == '\x01') {
            iVar7 = iVar7 + 1;
          }
        } while (iVar14 != 4);
        cVar3 = *(char *)(param_1 + 0x68);
        if (cVar3 != '\0') {
          if (cVar3 == '\x01') {
            if (*(char *)(iVar9 + 0x21) != '\x01') {
              *(undefined1 *)(iVar9 + 0x21) = 1;
              iVar4 = ((long long (*)(void))device_info_text_width_get)();
              iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_area_clear(iVar4 + 0xae,iVar9 + 4,iVar14 + 0x23c,iVar8 + 0x88);
            }
            if (iVar7 == 0) {
              ((long long (*)(void))cleanStocksIndex)();
            }
            if (2 < *piVar2) {
              if (*DAT_00039a20 == 0) {
                log_message(DAT_00039a28,DAT_00039a24,(uint)*(byte *)(param_1 + 0x68));
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            uVar5 = 0x43;
            goto LAB_0003998c;
          }
          if (cVar3 != '\x02') {
            return;
          }
          if (*(char *)(iVar9 + 0x21) != '\x02') {
            *(undefined1 *)(iVar9 + 0x21) = 2;
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar8 = ((long long (*)(void))device_info_text_width_get)();
            iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_area_clear(iVar14 + 0xae,iVar7 + 4,iVar8 + 0x23c,iVar12 + 0x88);
          }
          iVar14 = 0;
          iVar7 = 0;
          do {
            iVar8 = iVar14 * 0x7f2;
            iVar14 = iVar14 + 1;
            if (*(char *)(iVar4 + iVar8) == '\x01') {
              iVar7 = iVar7 + 1;
            }
          } while (iVar14 != 4);
          *(char *)(iVar9 + 4) = (char)iVar7;
          uVar17 = (uint)*(byte *)(iVar9 + 3);
          cVar3 = *(char *)(uVar17 * 0x7f2 + iVar4 + 1);
          if (cVar3 == '\0') {
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = iVar14 + 2;
            uVar5 = 0x46;
            iVar9 = iVar9 + 0xba;
LAB_00039ab6:
            gui_bmp_bitmap_draw(uVar5,iVar9,iVar14,0,0,0);
          }
          else {
            if (cVar3 == '\x01') {
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = iVar14 + 2;
              uVar5 = 0x44;
              iVar9 = iVar9 + 0xba;
              goto LAB_00039ab6;
            }
            if (cVar3 == '\x02') {
              iVar9 = ((long long (*)(void))device_info_text_width_get)();
              iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar14 = iVar14 + 2;
              uVar5 = 0x45;
              iVar9 = iVar9 + 0xba;
              goto LAB_00039ab6;
            }
          }
          if (iVar7 == 0) {
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_area_clear(iVar9 + 0x20e,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c);
          }
          else {
            local_80 = 0;
            memset_bytes(local_7c,0,0x1c);
            snprintf(&local_80,0x20,DAT_00039df4,uVar17 + 1,iVar7);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw(0,&local_80,0,iVar9 + 0x20e,iVar14 + 1,iVar7 + 0x23a,iVar8 + 0x1c,1,0,0,0,0
                        );
          }
          iVar12 = uVar17 * 0x7f2;
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          uVar5 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,iVar12 + 4 + iVar4,0,iVar9 + 0xd6,uVar5,iVar14 + 0x202,iVar7 + 0x1b,1,0,0,0
                       ,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,iVar4 + iVar12 + 0x24,0,iVar9 + 0xba,iVar14 + 0x1b,iVar7 + 0x234,
                       iVar8 + 0x36,1,0,0,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw_align_right(0,iVar4 + iVar12 + 100,0,iVar9 + 0x182,iVar14 + 0x36,iVar7 + 0x234,
                       iVar8 + 0x51,1,0,0,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw_align_right(0,iVar4 + iVar12 + 0x74,0,iVar9 + 0x182,iVar14 + 0x51,iVar7 + 0x234,
                       iVar8 + 0x6c,1,0,0,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw_align_right(0,iVar12 + 0x84 + iVar4,0,iVar9 + 0x182,iVar14 + 0x6c,iVar7 + 0x234,
                       iVar8 + 0x87,1,0,0,0,0);
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar4 = iVar12 + 0x94 + iVar4;
          iVar9 = iVar9 + 0x172;
          iVar8 = iVar8 + 0xba;
LAB_00038220:
          gui_bitmap_draw(iVar8,iVar7 + 0x36,iVar9,iVar14 + 0x88,iVar4,0xf);
          return;
        }
        if (*(char *)(iVar9 + 0x21) != '\0') {
          *(undefined1 *)(iVar9 + 0x21) = 0;
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_area_clear(iVar4 + 0xae,iVar9 + 4,iVar14 + 0x23c,iVar8 + 0x88);
        }
        if (iVar7 == 0) {
          ((long long (*)(void))cleanStocksIndex)();
        }
        if (2 < *piVar2) {
          if (*DAT_00039a20 == 0) {
            log_message(DAT_00039a28,DAT_00039a24,(uint)*(byte *)(param_1 + 0x68));
          }
          else {
            ((long long (*)(void))debug_print)();
          }
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        uVar5 = 0x43;
      }
      else {
        if (uVar17 != 2) {
          return;
        }
        iVar14 = 0;
        local_80 = 0;
        iVar7 = 0;
        memset_bytes(local_7c,0,0x1c);
        iVar4 = DAT_00039e04;
        do {
          if (*(char *)(iVar4 + iVar14 * 0x159) == '\x01') {
            if (2 < *piVar2) {
              if (*DAT_00039df8 == 0) {
                log_message(DAT_00039e00,DAT_00039dfc,iVar14);
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            iVar7 = iVar7 + 1;
          }
          iVar14 = iVar14 + 1;
        } while (iVar14 != 4);
        cVar3 = *(char *)(param_1 + 0x69);
        if (cVar3 != '\0') {
          if (cVar3 != '\x01') {
            if (cVar3 != '\x02') {
              return;
            }
            if (*(char *)(iVar9 + 0x22) != '\x02') {
              *(undefined1 *)(iVar9 + 0x22) = 2;
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar12 = ((long long (*)(void))device_info_text_width_get)();
              iVar16 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_area_clear(iVar14 + 0xae,iVar8 + 4,iVar12 + 0x23c,iVar16 + 0x88);
            }
            if (2 < *piVar2) {
              if (*DAT_0003a188 == 0) {
                log_message(DAT_0003a190,DAT_0003a18c,iVar7);
              }
              else {
                ((long long (*)(void))debug_print)();
              }
            }
            *(char *)(iVar9 + 6) = (char)iVar7;
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_bmp_bitmap_draw(0x47,iVar14 + 0xba,iVar8 + 2,0,0,0);
            if (iVar7 != 0) {
              *(undefined1 *)(iVar9 + 8) = 1;
              memset_bytes(&local_80,0,0x20);
              snprintf(&local_80,0x20,DAT_0003a198,*(byte *)(iVar9 + 5) + 1,iVar7);
              iVar9 = (uint)*(byte *)(iVar9 + 5) * 0x159;
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar12 = ((long long (*)(void))device_info_text_width_get)();
              iVar16 = ((long long (*)(void))device_info_text_height_get_clamped)();
              gui_utf_draw(0,iVar9 + 1 + iVar4,0,iVar14 + 0xd6,iVar8 + 1,iVar12 + 0x200,
                           iVar16 + 0x1c,1,0,0,0,0);
              if (iVar7 == 1) {
                iVar14 = ((long long (*)(void))device_info_text_width_get)();
                iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar8 = ((long long (*)(void))device_info_text_width_get)();
                iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
                puVar10 = DAT_0003a19c;
              }
              else {
                iVar14 = ((long long (*)(void))device_info_text_width_get)();
                iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
                iVar8 = ((long long (*)(void))device_info_text_width_get)();
                iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
                puVar10 = &local_80;
              }
              gui_utf_draw(0,puVar10,0,iVar14 + 0x216,iVar7 + 1,iVar8 + 0x23a,iVar12 + 0x1c,1,0,0,0,
                           0);
              iVar14 = ((long long (*)(void))device_info_text_width_get)();
              iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = ((long long (*)(void))device_info_text_width_get)();
              iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
              iVar7 = iVar7 + 0x236;
              iVar14 = iVar14 + 0xba;
LAB_00038708:
              iVar12 = iVar12 + 0x88;
              iVar8 = iVar8 + 0x1c;
              iVar4 = iVar9 + 0x41 + iVar4;
              goto LAB_00037d2a;
            }
            iVar4 = dashboard_read_word(DAT_0003a194);
            if ((-1 < iVar4 << 0x1e) || (*(char *)(iVar9 + 8) != '\x01')) goto LAB_000385f0;
            *(char *)(iVar9 + 8) = (char)iVar7;
            iVar4 = ((long long (*)(void))get_device_info)();
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0xd4,iVar14 + 1,iVar7 + 0x23c,iVar8 + 0x1c);
            iVar4 = ((long long (*)(void))get_device_info)();
            uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
            iVar4 = ((long long (*)(void))get_device_info)();
            uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xd4,iVar9 + 1,iVar14 + 0x23c,iVar7 + 0x1c);
            iVar4 = ((long long (*)(void))get_device_info)();
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar7 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0xba,iVar14 + 0x1c,iVar7 + 0x234,iVar8 + 0x88);
            iVar4 = ((long long (*)(void))get_device_info)();
            uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
            iVar4 = ((long long (*)(void))get_device_info)();
            uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar9 = iVar9 + 0x234;
            iVar4 = iVar4 + 0xba;
LAB_000385e8:
            reflash_fb_data_to_lcd(uVar5,uVar6,iVar4,iVar14 + 0x1c,iVar9,iVar7 + 0x88);
LAB_000385f0:
            ((long long (*)(void))cleanNewsIndex)();
            return;
          }
          if (*(char *)(iVar9 + 0x22) != '\x01') {
            *(undefined1 *)(iVar9 + 0x22) = 1;
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_area_clear(iVar4 + 0xae,iVar9 + 4,iVar14 + 0x23c,iVar8 + 0x88);
          }
          if (iVar7 == 0) {
            ((long long (*)(void))cleanNewsIndex)();
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          uVar5 = 0x47;
LAB_0003998c:
          gui_bmp_bitmap_draw(uVar5,iVar4 + 0xba,iVar9 + 2,0,0,0);
          iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
          if (iVar4 == 6) {
            iVar4 = ((long long (*)(void))device_info_text_width_get)();
            iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            gui_utf_draw(0,DAT_0003a184,0,iVar4 + 0x108,iVar9 + 0x2a,iVar14 + 0x236,iVar7 + 0x45,1,0
                         ,0,0,0);
            iVar9 = ((long long (*)(void))device_info_text_width_get)();
            iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar14 = ((long long (*)(void))device_info_text_width_get)();
            iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
            iVar9 = iVar9 + 0x132;
            goto LAB_0003846c;
          }
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,DAT_00039a2c,0,iVar4 + 0x12a,iVar9 + 0x2a,iVar14 + 0x236,iVar7 + 0x45,1,0,0
                       ,0,0);
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar9 = iVar9 + 0x12a;
LAB_00037fac:
          iVar7 = iVar7 + 0x60;
          iVar14 = iVar14 + 0x236;
          iVar4 = iVar4 + 0x45;
          uVar5 = DAT_00038278;
          goto LAB_00037e92;
        }
        if (*(char *)(iVar9 + 0x22) != '\0') {
          *(undefined1 *)(iVar9 + 0x22) = 0;
          iVar4 = ((long long (*)(void))device_info_text_width_get)();
          iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_area_clear(iVar4 + 0xae,iVar9 + 4,iVar14 + 0x23c,iVar8 + 0x88);
        }
        if (iVar7 == 0) {
          ((long long (*)(void))cleanNewsIndex)();
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        uVar5 = 0x47;
      }
      gui_bmp_bitmap_draw(uVar5,iVar4 + 0xba,iVar9 + 2,0,0,0);
      iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
      if (iVar4 == 6) {
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = iVar7 + 0x51;
        iVar14 = iVar14 + 0x236;
        iVar4 = iVar4 + 0x36;
        iVar9 = iVar9 + 0x154;
        uVar5 = DAT_00037eb4;
        goto LAB_00037e92;
      }
      iVar9 = ((long long (*)(void))device_info_text_width_get)();
      iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar9 = iVar9 + 0x154;
LAB_00037e4a:
      iVar7 = iVar7 + 0x51;
      iVar14 = iVar14 + 0x236;
      iVar4 = iVar4 + 0x36;
      uVar5 = DAT_00037eb0;
      goto LAB_00037e92;
    }
    local_80 = uVar17;
    memset_bytes(local_7c,0,0x1c);
    iVar4 = 0;
    iVar14 = 0;
    do {
      if (*(char *)(iVar4 * 0x143 + *(int *)(param_2 + 0x1020) + 3) == '\x01') {
        if (2 < *piVar2) {
          if (*DAT_0003925c == 0) {
            log_message(DAT_0003927c,DAT_00039268,iVar4);
          }
          else {
            ((long long (*)(void))debug_print)();
          }
        }
        iVar14 = iVar14 + 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 4);
    if (2 < *piVar2) {
      if (*DAT_0003925c == 0) {
        log_message(DAT_00039280,DAT_00039268,iVar14);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
    *(char *)(iVar9 + 2) = (char)iVar14;
    iVar4 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_bmp_bitmap_draw(0x3b,iVar4 + 0xba,iVar7 + 1,0,0,0);
    if (iVar14 != 0) {
      *(undefined1 *)(iVar9 + 7) = 1;
      memset_bytes(&local_80,0,0x20);
      snprintf(&local_80,0x20,DAT_00039a1c,*(byte *)(iVar9 + 1) + 1,iVar14);
      iVar12 = (uint)*(byte *)(iVar9 + 1) * 0x143;
      local_c8 = *(int *)(param_2 + 0x1020) + iVar12 + 4;
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
LAB_000397a0:
      gui_utf_draw(0,local_c8,0,iVar8 + 0xd6,iVar9 + 1,iVar4 + 0x22e,iVar7 + 0x1c,1,0,0,0,0);
      if (iVar14 == 1) {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        puVar10 = DAT_0003a878;
      }
      else {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        puVar10 = &local_80;
      }
      gui_utf_draw(0,puVar10,0,iVar4 + 0x20e,iVar9 + 1,iVar7 + 0x23a,iVar14 + 0x1c,1,0,0,0,0);
      iVar4 = iVar12 + 0x2d + *(int *)(param_2 + 0x1020);
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar12 = iVar12 + 0x88;
      iVar7 = iVar7 + 0x238;
      iVar8 = iVar8 + 0x1c;
      iVar14 = iVar14 + 0xba;
      goto LAB_00037d2a;
    }
    iVar4 = dashboard_read_word(DAT_00039284);
    if ((iVar4 << 0x1e < 0) && (*(char *)(iVar9 + 7) == '\x01')) {
      *(char *)(iVar9 + 7) = (char)iVar14;
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0xd6,iVar7 + 1,iVar8 + 0x22e,iVar12 + 0x1c);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xd6,iVar14 + 1,iVar7 + 0x22e,iVar8 + 0x1c);
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0xba,iVar7 + 0x1c,iVar8 + 0x238,iVar12 + 0x88);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xba,iVar14 + 0x1c,iVar7 + 0x238,iVar8 + 0x88);
    }
    ((long long (*)(void))reset_touch_selection_state)();
    uVar17 = ((long long (*)(void))get_ui_mode_flag_byte1)();
    if (*(byte *)(iVar9 + 0x18) != uVar17) {
      *(char *)(iVar9 + 0x18) = (char)uVar17;
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar9 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0xd2,iVar14 + 0x1c,iVar7 + 0x232,iVar8 + 0x88);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xd2,iVar9 + 0x1c,iVar14 + 0x232,iVar7 + 0x88);
    }
    if (uVar17 != 6) {
LAB_00039318:
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,DAT_00039614,0,iVar4 + 0x11c,iVar9 + 0x28,iVar14 + 0x236,iVar7 + 0x43,1,0,0,0,0
                  );
      iVar9 = ((long long (*)(void))device_info_text_width_get)();
      iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = iVar14 + 0x236;
      iVar9 = iVar9 + 0x128;
      goto LAB_00038ad4;
    }
    iVar4 = ((long long (*)(void))device_info_text_width_get)();
    iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_utf_draw(0,DAT_00039a14,0,iVar4 + 0x10a,iVar9 + 0x28,iVar14 + 0x236,iVar7 + 0x43,1,0,0,0,0);
    iVar9 = ((long long (*)(void))device_info_text_width_get)();
    iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = iVar14 + 0x236;
    iVar9 = iVar9 + 0x132;
  }
  else {
    uVar5 = ((long long (*)(void))get_timestamp)();
    unix_timestamp_to_datetime(uVar5,&local_a4);
    uVar5 = get_localized_weekday_name((char)uStack_a2 + '.');
    cVar3 = compute_day_of_week(CONCAT11(uStack_a3,local_a4),uStack_a2,CONCAT11(uStack_9f,local_a0));
    uVar6 = get_localized_weekday_name(cVar3 + '(');
    local_94 = 0;
    local_90 = 0;
    local_8c = 0;
    uStack_88 = 0;
    vdprintf_to_fd(&local_94,0,0x10,DAT_0003a514,uVar6,uVar5,CONCAT11(uStack_9f,local_a0));
    uVar5 = ((long long (*)(void))device_info_text_width_get)();
    uVar6 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar4 = ((long long (*)(void))device_info_text_width_get)();
    iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_utf_draw(0,&local_94,3,uVar5,uVar6,iVar4 + 0xa0,iVar14 + 0x1b,1,0,0,0,0);
    iVar4 = ((long long (*)(void))get_device_info)();
    iVar4 = *(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e) - 1;
    if (iVar4 != 0) {
      iVar4 = 1;
    }
    uVar5 = ((long long (*)(void))get_timestamp)();
    uVar6 = ((long long (*)(void))device_info_text_width_get)();
    iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar7 = ((long long (*)(void))device_info_text_width_get)();
    iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_clock_draw(uVar5,uVar6,iVar14 + 0x34,iVar7 + 0x96,iVar8 + 0x55,1,iVar4);
    if (param_3 == 1) {
      uVar5 = ((long long (*)(void))device_info_text_width_get)();
      iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x3e,uVar5,iVar4 + 0x6d,0,0,0);
      if (*(char *)(param_1 + 0x5f) == '\x01') {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x42,iVar4 + 0x60,iVar14 + 0x6d,0,0,0);
      }
      else {
        iVar4 = ((long long (*)(void))get_device_info)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar8 = ((long long (*)(void))device_info_text_width_get)();
        iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
        clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0x60,iVar7 + 0x6d,iVar8 + 0x78,iVar12 + 0x88);
        iVar4 = ((long long (*)(void))get_device_info)();
        uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
        iVar4 = ((long long (*)(void))get_device_info)();
        uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0x60,iVar14 + 0x6d,iVar7 + 0x78,iVar8 + 0x88);
      }
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x4f,iVar4 + 0x240,iVar14 + 4,0,0,0);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bmp_bitmap_draw(0x4e,iVar4 + 0xac,iVar14 + 4,0,0,0);
    }
    else if (param_3 != 4) {
      return;
    }
    uVar17 = (uint)*(byte *)(iVar9 + 0x1a);
    if (uVar17 != 0) {
      if (uVar17 == 1) {
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x43,iVar4 + 0xba,iVar9 + 2,0,0,0);
        iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
        if (iVar4 != 6) {
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = iVar14 + 0x208;
          iVar7 = iVar7 + 0x51;
          iVar4 = iVar4 + 0x36;
          iVar9 = iVar9 + 0x108;
          uVar5 = DAT_00038f58;
          goto LAB_00037e92;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,DAT_0003a87c,0,iVar4 + 0x118,iVar9 + 0x31,iVar14 + 0x230,iVar7 + 0x4c,1,0,0,0
                     ,0);
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      }
      else {
        if (uVar17 != 2) {
          return;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bmp_bitmap_draw(0x47,iVar4 + 0xba,iVar9 + 2,0,0,0);
        iVar4 = ((long long (*)(void))get_ui_mode_flag_byte1)();
        if (iVar4 != 6) {
          iVar9 = ((long long (*)(void))device_info_text_width_get)();
          iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar14 = ((long long (*)(void))device_info_text_width_get)();
          iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar7 = iVar7 + 0x51;
          iVar14 = iVar14 + 0x208;
          iVar4 = iVar4 + 0x36;
          iVar9 = iVar9 + 0x108;
          uVar5 = DAT_00038f58;
          goto LAB_00037e92;
        }
        iVar4 = ((long long (*)(void))device_info_text_width_get)();
        iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,DAT_0003a87c,0,iVar4 + 0x118,iVar9 + 0x31,iVar14 + 0x230,iVar7 + 0x4c,1,0,0,0
                     ,0);
        iVar9 = ((long long (*)(void))device_info_text_width_get)();
        iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      }
      iVar14 = iVar14 + 0x230;
      iVar9 = iVar9 + 0x122;
LAB_00038e72:
      iVar7 = iVar7 + 0x67;
      iVar4 = iVar4 + 0x4c;
      uVar5 = DAT_00038f60;
      goto LAB_00037e92;
    }
    local_80 = uVar17;
    memset_bytes(local_7c,0,0x1c);
    iVar4 = 0;
    iVar14 = 0;
    do {
      if (*(char *)(iVar4 * 0x143 + *(int *)(param_2 + 0x1020) + 3) == '\x01') {
        if (2 < *piVar2) {
          if (*DAT_0003a518 == 0) {
            log_message(DAT_0003a520,DAT_0003a51c,iVar4);
          }
          else {
            ((long long (*)(void))debug_print)();
          }
        }
        iVar14 = iVar14 + 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 4);
    if (2 < *piVar2) {
      if (*DAT_0003a518 == 0) {
        log_message(DAT_0003a524,DAT_0003a51c,iVar14);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
    *(char *)(iVar9 + 2) = (char)iVar14;
    iVar4 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_bmp_bitmap_draw(0x3b,iVar4 + 0xba,iVar7 + 1,0,0,0);
    if (iVar14 != 0) {
      *(undefined1 *)(iVar9 + 7) = 1;
      memset_bytes(&local_80,0,0x20);
      snprintf(&local_80,0x20,DAT_0003a874,*(byte *)(iVar9 + 1) + 1,iVar14);
      iVar12 = (uint)*(byte *)(iVar9 + 1) * 0x143;
      local_c8 = *(int *)(param_2 + 0x1020) + iVar12 + 4;
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      goto LAB_000397a0;
    }
    iVar4 = dashboard_read_word(DAT_0003a528);
    if ((iVar4 << 0x1e < 0) && (*(char *)(iVar9 + 7) == '\x01')) {
      *(char *)(iVar9 + 7) = (char)iVar14;
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0xd6,iVar7 + 1,iVar8 + 0x22e,iVar12 + 0x1c);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xd6,iVar14 + 1,iVar7 + 0x22e,iVar8 + 0x1c);
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar4 + 0xb90,0,iVar14 + 0xba,iVar7 + 0x1c,iVar8 + 0x238,iVar12 + 0x88);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xba,iVar14 + 0x1c,iVar7 + 0x238,iVar8 + 0x88);
    }
    ((long long (*)(void))reset_touch_selection_state)();
    uVar17 = ((long long (*)(void))get_ui_mode_flag_byte1)();
    if (*(byte *)(iVar9 + 0x18) != uVar17) {
      *(char *)(iVar9 + 0x18) = (char)uVar17;
      iVar4 = ((long long (*)(void))get_device_info)();
      iVar9 = ((long long (*)(void))device_info_text_width_get)();
      iVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar4 + 0xb90,0,iVar9 + 0xd2,iVar14 + 0x1c,iVar7 + 0x232,iVar8 + 0x88);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar5 = *(undefined4 *)(iVar4 + 0xeb4);
      iVar4 = ((long long (*)(void))get_device_info)();
      uVar6 = *(undefined4 *)(iVar4 + 0xeb8);
      iVar4 = ((long long (*)(void))device_info_text_width_get)();
      iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar5,uVar6,iVar4 + 0xd2,iVar9 + 0x1c,iVar14 + 0x232,iVar7 + 0x88);
    }
    if (uVar17 != 6) goto LAB_00039318;
    iVar4 = ((long long (*)(void))device_info_text_width_get)();
    iVar9 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_utf_draw(0,DAT_0003a52c,0,iVar4 + 0x10a,iVar9 + 0x28,iVar14 + 0x236,iVar7 + 0x43,1,0,0,0,0);
    iVar9 = ((long long (*)(void))device_info_text_width_get)();
    iVar4 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = ((long long (*)(void))device_info_text_width_get)();
    iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar14 = iVar14 + 0x236;
LAB_00038c66:
    iVar9 = iVar9 + 0x130;
  }
  iVar7 = iVar7 + 0x5e;
  iVar4 = iVar4 + 0x43;
  uVar5 = DAT_00039a18;
LAB_00037e92:
  gui_utf_draw(0,uVar5,0,iVar9,iVar4,iVar14,iVar7,1,0,0,0,0);
  return;
}
