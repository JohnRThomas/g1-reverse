#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003e7f8 @ 0x0003e7f8
 * public-name: navigation_panoramic_map_display
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_bitmps_merge_draw                    <= FUN_00043bd8 @ 0x00043bd8
 *   gui_4bit_bitmap_override                 <= FUN_00043d78 @ 0x00043d78
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   decode_rle_byte_pairs                    <= FUN_0007da70 @ 0x0007da70
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_a9ee1                             @ 0x000a9ee1   [INLINED -- refactor stage 01]
 *   rodata_a9eff                             @ 0x000a9eff   [INLINED -- refactor stage 01]
 *   rodata_a9f6f                             @ 0x000a9f6f   [INLINED -- refactor stage 01]
 *   rodata_a9f93                             @ 0x000a9f93   [INLINED -- refactor stage 01]
 *   rodata_a9fcd                             @ 0x000a9fcd
 *   rodata_a9fe6                             @ 0x000a9fe6
 *   rodata_a9ff7                             @ 0x000a9ff7
 *   rodata_aa01a                             @ 0x000aa01a
 *   rodata_aa425                             @ 0x000aa425   [INLINED -- refactor stage 01]
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_level                              @ 0x2000230c
 *   g_ipc_or_evt_ctx                         @ 0x20004bb8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ble_work_queue                         @ 0x20007574
 *   g_20010322                               @ 0x20010322
 *   g_20010323                               @ 0x20010323
 *   g_20010324                               @ 0x20010324
 *   g_20010325                               @ 0x20010325
 *   g_20011d82                               @ 0x20011d82
 *   g_20013dea                               @ 0x20013dea
 *   g_20015e52                               @ 0x20015e52
 *   g_2001ba2c                               @ 0x2001ba2c
 *   g_2001ba2d                               @ 0x2001ba2d
 *   g_buf_2001ba2e                           @ 0x2001ba2e
 */
/* Reconstructed navigation_panoramic_map_display @ 0x3e7f8  (parity: 298/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../../headers/g1_log.h"
#include "../../../../headers/g1_dedupe.h"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong;

extern int get_device_info(void);
extern long long reflash_fb_data_to_lcd(int, ...);
extern long long gui_canvas_flags_clear_bit1(int, ...);
extern long long clean_fb_data(int, ...);
extern long long device_info_text_width_get(int, ...);
extern long long device_info_text_height_get_clamped(int, ...);
extern int gui_bitmps_merge_draw(unsigned int, int, int, int, int, int, unsigned char, unsigned char);
extern long long gui_4bit_bitmap_override(int, ...);
extern long long gui_utf_draw(int, ...);
extern int get_ui_mode_flag_byte1(void);
extern long long get_timestamp(int, ...);
extern long long gui_clock_draw(int, ...);
extern long long gui_canvas_flags_set_bit1(int, ...);
extern long long memset_bytes(int, ...);
extern long long thunk_FUN_000723b8(int, ...);
extern void memcpy(int, int, int);
extern unsigned long decode_rle_byte_pairs(const unsigned char*, unsigned long, unsigned char*);
extern long long thunk_FUN_00072558(int, ...);
extern long long FUN_0007d376(int, ...);
extern long long FUN_0007d37a(uint32_t);

#define DAT_0003e8b0 (((unsigned long)g_ipc_or_evt_ctx) /*=0x20004bb8*/)
#define DAT_0003e8b4 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0003e8b8 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0003e8bc (((unsigned long)"navigation_panoramic_map_display") /*=0xaa425*/)
#define DAT_0003e8c0 (((unsigned long)"%s(): reflash panoramic map to lcd\n") /*=0xa9f6f*/)
#define DAT_0003e8c4 (((unsigned long)&rodata_aae20) /*=0xaae20*/)
#define DAT_0003ec44 ((volatile char*)((unsigned long)&g_20010325) /*=0x20010325*/)
#define DAT_0003ec48 (((unsigned long)&g_20013dea) /*=0x20013dea*/)
#define DAT_0003ec4c (((unsigned long)&g_20011d82) /*=0x20011d82*/)
#define DAT_0003ec50 (((unsigned long)&rodata_aae20) /*=0xaae20*/)
#define DAT_0003ec54 ((volatile char*)((unsigned long)&g_20010322) /*=0x20010322*/)
#define DAT_0003ec58 ((volatile undefined1*)((unsigned long)&g_2001ba2c) /*=0x2001ba2c*/)
#define DAT_0003ec5c ((volatile undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/)
#define DAT_0003ef48 (((unsigned long)&g_20013dea) /*=0x20013dea*/)
#define DAT_0003ef4c (((unsigned long)&g_20011d82) /*=0x20011d82*/)
#define DAT_0003ef50 ((volatile char*)((unsigned long)&g_2001ba2c) /*=0x2001ba2c*/)
#define DAT_0003ef54 ((volatile char*)((unsigned long)&g_20010324) /*=0x20010324*/)
#define DAT_0003ef58 ((volatile char*)((unsigned long)&g_20010325) /*=0x20010325*/)
#define DAT_0003ef5c ((volatile char*)((unsigned long)&g_20010323) /*=0x20010323*/)
#define DAT_0003ef60 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0003ef64 ((volatile undefined1*)((unsigned long)&g_2001ba2d) /*=0x2001ba2d*/)
#define DAT_0003ef68 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0003ef6c (((unsigned long)"navigation_panoramic_map_display") /*=0xaa425*/)
#define DAT_0003ef70 (((unsigned long)"%s(): Data is in raw format.\n") /*=0xa9ee1*/)
#define DAT_0003ef74 (((unsigned long)g_buf_2001ba2e) /*=0x2001ba2e*/)
#define DAT_0003ef78 (((unsigned long)&g_ble_work_queue) /*=0x20007574*/)
#define DAT_0003ef7c (((unsigned long)&g_20015e52) /*=0x20015e52*/)
#define DAT_0003ef80 (((unsigned long)"%s(): APP send navigation offset overstep ,stop draw....\n") /*=0xa9f93*/)
#define DAT_0003f278 (((unsigned long)&rodata_a9fcd) /*=0xa9fcd*/)
#define DAT_0003f27c (((unsigned long)&rodata_a9fe6) /*=0xa9fe6*/)
#define DAT_0003f280 (((unsigned long)&rodata_a9ff7) /*=0xa9ff7*/)
#define DAT_0003f284 (((unsigned long)&rodata_aa01a) /*=0xaa01a*/)
#define DAT_0003f288 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0003f28c ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0003f290 (((unsigned long)"navigation_panoramic_map_display") /*=0xaa425*/)
#define DAT_0003f294 (((unsigned long)"%s(): APP send navigation offset overstep ,stop draw....\n") /*=0xa9f93*/)
#define DAT_0003f298 (((unsigned long)"%s(): Data is in rle compress raw format.\n") /*=0xa9eff*/)
#define DAT_0003f29c (((unsigned long)g_buf_2001ba2e) /*=0x2001ba2e*/)
#define DAT_0003f2a0 (((unsigned long)&g_ble_work_queue) /*=0x20007574*/)
#define DAT_0003f2a4 (((unsigned long)&g_20015e52) /*=0x20015e52*/)

void navigation_panoramic_map_display(undefined4 param_1,int param_2)
{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  uint uVar16;
  undefined4 uVar17;
  undefined8 uVar32;
  undefined4 local_30;
  undefined4 uStack_2c;

  iVar4 = DAT_0003e8b0;
  if (*(char *)(DAT_0003e8b0 + 4) == '\0') {
    if (2 < *DAT_0003e8b4) {
      if (*DAT_0003e8b8 == 0) {
        log_message(DAT_0003e8c0,DAT_0003e8bc);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
    iVar7 = ((long long (*)(void))get_device_info)();
    iVar8 = DAT_0003e8c4;
    iVar15 = 0x640;
    iVar7 = iVar7 + 0xb90;
    while( 1 ) {
      uVar16 = 0;
      do {
        iVar12 = 0;
        do {
          iVar13 = *(int *)(iVar7 + uVar16 * 4);
          bVar1 = *(byte *)(iVar13 + iVar12);
          if (bVar1 != 0) {
            *(byte *)(iVar13 + iVar12) =
                 bVar1 & *(byte *)((uVar16 % 0x1a) * 0xa00 + iVar15 + iVar8 + iVar12);
          }
          iVar12 = iVar12 + 1;
        } while (iVar12 != 0x140);
        uVar16 = uVar16 + 1;
      } while (uVar16 != 199);
      iVar12 = ((long long (*)(void))get_device_info)();
      uVar14 = *(undefined4 *)(iVar12 + 0xeb4);
      iVar12 = ((long long (*)(void))get_device_info)();
      reflash_fb_data_to_lcd(uVar14,*(undefined4 *)(iVar12 + 0xeb8),0,0,0x280,199);
      if (iVar15 == 0x500) break;
      iVar15 = 0x500;
    }
    ((long long (*)(void))gui_canvas_flags_clear_bit1)();
    iVar15 = 1;
    do {
      clean_fb_data(iVar7,0,0,0,0x280,199);
      puVar5 = (undefined1 *)DAT_0003ec58;
      if (*DAT_0003ec44 == '\x01') {
        iVar8 = ((long long (*)(void))device_info_text_width_get)();
        uVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar12 = ((long long (*)(void))device_info_text_width_get)();
        iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_bitmps_merge_draw(iVar8 + 0x58,uVar14,iVar12 + 0x240,iVar13 + 0x88,DAT_0003ec4c,DAT_0003ec48,2,
                     0xf);
        uVar2 = *(ushort *)(param_2 + 8);
        if ((uVar2 < 0x1e9) && (*(ushort *)(param_2 + 10) < 0x89)) {
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          uVar3 = *(ushort *)(param_2 + 10);
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_4bit_bitmap_override(0x54,(uint)uVar2 + iVar8 + 0x52,(uVar3 - 6) + iVar12);
        }
        else if (0 < *DAT_0003ef60) {
          if (*DAT_0003ef68 == 0) {
            log_message(DAT_0003ef80,DAT_0003ef6c);
          }
          else {
            ((long long (*)(void))debug_print)();
          }
        }
        uVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar12 = ((long long (*)(void))device_info_text_width_get)();
        iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,param_2 + 0x95,0,uVar14,iVar8 + 0x37,iVar12 + 0x4c,iVar13 + 0x52,1,0,0,0,0);
        uVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar12 = ((long long (*)(void))device_info_text_width_get)();
        iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,param_2 + 0xd,0,uVar14,iVar8 + 0x52,iVar12 + 0x4c,iVar13 + 0x6d,1,0,0,0,0);
        uVar14 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar12 = ((long long (*)(void))device_info_text_width_get)();
        iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,param_2 + 0x25,0,uVar14,iVar8 + 0x6d,iVar12 + 0x4c,iVar13 + 0x88,1,0,0,0,0);
        *puVar5 = 1;
      }
      else {
        iVar8 = ((long long (*)(void))get_ui_mode_flag_byte1)();
        if (iVar8 == 6) {
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar13 = ((long long (*)(void))device_info_text_width_get)();
          iVar10 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,DAT_0003f280,0,iVar8 + 0x7a,iVar12 + 0x37,iVar13 + 0x23a,iVar10 + 0x52,1,0,
                       0,0,0);
          iVar12 = ((long long (*)(void))device_info_text_width_get)();
          iVar11 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar13 = ((long long (*)(void))device_info_text_width_get)();
          iVar10 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar13 = iVar13 + 0x23a;
          iVar12 = iVar12 + 0xd1;
          iVar8 = DAT_0003f284;
        }
        else {
          iVar8 = ((long long (*)(void))device_info_text_width_get)();
          iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar13 = ((long long (*)(void))device_info_text_width_get)();
          iVar10 = ((long long (*)(void))device_info_text_height_get_clamped)();
          gui_utf_draw(0,DAT_0003f278,0,iVar8 + 0xb0,iVar12 + 0x37,iVar13 + 0x226,iVar10 + 0x52,1,0,
                       0,0,0);
          iVar12 = ((long long (*)(void))device_info_text_width_get)();
          iVar11 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar13 = ((long long (*)(void))device_info_text_width_get)();
          iVar10 = ((long long (*)(void))device_info_text_height_get_clamped)();
          iVar13 = iVar13 + 0x226;
          iVar12 = iVar12 + 0xda;
          iVar8 = DAT_0003f27c;
        }
        gui_utf_draw(0,iVar8,0,iVar12,iVar11 + 0x52,iVar13,iVar10 + 0x6d,1,0,0,0,0);
        *puVar5 = 0;
      }
      iVar8 = ((long long (*)(void))get_device_info)();
      iVar8 = *(byte *)(*(int *)(iVar8 + 0xfec) + 0x5e) - 1;
      if (iVar8 != 0) {
        iVar8 = 1;
      }
      uVar14 = ((long long (*)(void))get_timestamp)();
      uVar9 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar13 = ((long long (*)(void))device_info_text_width_get)();
      iVar10 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_clock_draw(uVar14,uVar9,iVar12 + 2,iVar13 + 0x4c,iVar10 + 0x1d,3,iVar8);
      puVar6 = (undefined4 *)DAT_0003ec5c;
      uVar16 = 0;
      local_30 = *DAT_0003ec5c;
      do {
        iVar8 = 0;
        uStack_2c = puVar6[1];
        do {
          iVar12 = *(int *)(iVar7 + uVar16 * 4);
          bVar1 = *(byte *)(iVar12 + iVar8);
          if (bVar1 != 0) {
            *(byte *)(iVar12 + iVar8) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar15) * 0x140 +
                                   (uVar16 % 0x1a) * 0xa00 + DAT_0003ec50 + iVar8);
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 != 0x140);
        uVar16 = uVar16 + 1;
      } while (uVar16 != 199);
      iVar8 = ((long long (*)(void))get_device_info)();
      uVar14 = *(undefined4 *)(iVar8 + 0xeb4);
      iVar8 = ((long long (*)(void))get_device_info)();
      iVar15 = iVar15 + 1;
      reflash_fb_data_to_lcd(uVar14,*(undefined4 *)(iVar8 + 0xeb8),0,0,0x280,199);
    } while (iVar15 != 4);
    ((long long (*)(void))gui_canvas_flags_set_bit1)();
    if (*DAT_0003ec44 == '\x01') {
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0x95,0,uVar14,iVar15 + 0x37,iVar8 + 0x4c,iVar7 + 0x52,1,0,0,0,0);
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0xd,0,uVar14,iVar15 + 0x52,iVar8 + 0x4c,iVar7 + 0x6d,1,0,0,0,0);
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0x25,0,uVar14,iVar15 + 0x6d,iVar8 + 0x4c,iVar7 + 0x88,1,0,0,0,0);
    }
    iVar15 = ((long long (*)(void))get_device_info)();
    iVar15 = *(byte *)(*(int *)(iVar15 + 0xfec) + 0x5e) - 1;
    if (iVar15 != 0) {
      iVar15 = 1;
    }
    uVar14 = ((long long (*)(void))get_timestamp)();
    uVar9 = ((long long (*)(void))device_info_text_width_get)();
    iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar7 = ((long long (*)(void))device_info_text_width_get)();
    iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_clock_draw(uVar14,uVar9,iVar8 + 2,iVar7 + 0x4c,iVar12 + 0x1d,3,iVar15);
  }
  if (*DAT_0003ec54 == '\x01') {
    *DAT_0003ec54 = '\0';
    if (*DAT_0003ec44 == '\x01') {
      iVar15 = ((long long (*)(void))device_info_text_width_get)();
      uVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_bitmps_merge_draw(iVar15 + 0x58,uVar14,iVar8 + 0x240,iVar7 + 0x88,DAT_0003ef4c,DAT_0003ef48,2,0xf);
      uVar2 = *(ushort *)(param_2 + 8);
      if ((uVar2 < 0x1e9) && (*(ushort *)(param_2 + 10) < 0x89)) {
        iVar15 = ((long long (*)(void))device_info_text_width_get)();
        uVar3 = *(ushort *)(param_2 + 10);
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_4bit_bitmap_override(0x54,(uint)uVar2 + iVar15 + 0x52,(uVar3 - 6) + iVar8);
      }
      else if (0 < *DAT_0003f288) {
        if (*DAT_0003f28c == 0) {
          log_message(DAT_0003f294,DAT_0003f290);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      if (*DAT_0003ef50 != '\0') goto LAB_0003ed90;
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0x95,0,uVar14,iVar15 + 0x37,iVar8 + 0x4c,iVar7 + 0x52,1,0,0,0,0);
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0xd,0,uVar14,iVar15 + 0x52,iVar8 + 0x4c,iVar7 + 0x6d,1,0,0,0,0);
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar12 = ((long long (*)(void))device_info_text_width_get)();
      iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar12 = iVar12 + 0x4c;
      iVar13 = iVar13 + 0x88;
      iVar7 = iVar7 + 0x6d;
      iVar15 = param_2 + 0x25;
    }
    else {
      iVar15 = ((long long (*)(void))get_device_info)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      uVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar7 = ((long long (*)(void))device_info_text_width_get)();
      iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
      clean_fb_data(iVar15 + 0xb90,0,iVar8 + 0x58,uVar14,iVar7 + 0x240,iVar12 + 0x88);
      iVar15 = ((long long (*)(void))get_device_info)();
      uVar9 = *(undefined4 *)(iVar15 + 0xeb4);
      iVar15 = ((long long (*)(void))get_device_info)();
      uVar17 = *(undefined4 *)(iVar15 + 0xeb8);
      iVar15 = ((long long (*)(void))device_info_text_width_get)();
      uVar14 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      reflash_fb_data_to_lcd(uVar9,uVar17,iVar15 + 0x58,uVar14,iVar8 + 0x240,iVar7 + 0x88);
      iVar15 = ((long long (*)(void))get_ui_mode_flag_byte1)();
      if (iVar15 == 6) {
        iVar15 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,DAT_0003f280,0,iVar15 + 0x7a,iVar8 + 0x37,iVar7 + 0x23a,iVar12 + 0x52,1,0,0,0
                     ,0);
        iVar8 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar12 = ((long long (*)(void))device_info_text_width_get)();
        iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = iVar7 + 0x52;
        iVar12 = iVar12 + 0x23a;
        iVar13 = iVar13 + 0x6d;
        iVar8 = iVar8 + 0xd1;
        iVar15 = DAT_0003f284;
      }
      else {
        iVar15 = ((long long (*)(void))device_info_text_width_get)();
        iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = ((long long (*)(void))device_info_text_width_get)();
        iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
        gui_utf_draw(0,DAT_0003f278,0,iVar15 + 0xb0,iVar8 + 0x37,iVar7 + 0x226,iVar12 + 0x52,1,0,0,0
                     ,0);
        iVar8 = ((long long (*)(void))device_info_text_width_get)();
        iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar12 = ((long long (*)(void))device_info_text_width_get)();
        iVar13 = ((long long (*)(void))device_info_text_height_get_clamped)();
        iVar7 = iVar7 + 0x52;
        iVar12 = iVar12 + 0x226;
        iVar13 = iVar13 + 0x6d;
        iVar8 = iVar8 + 0xda;
        iVar15 = DAT_0003f27c;
      }
    }
    gui_utf_draw(0,iVar15,0,iVar8,iVar7,iVar12,iVar13,1,0,0,0,0);
  }
LAB_0003ed90:
  if (*DAT_0003ef54 == '\x01') {
    *DAT_0003ef54 = '\0';
    if (*DAT_0003ef58 == '\x01') {
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0x95,0,uVar14,iVar15 + 0x37,iVar8 + 0x4c,iVar7 + 0x52,1,0,0,0,0);
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0xd,0,uVar14,iVar15 + 0x52,iVar8 + 0x4c,iVar7 + 0x6d,1,0,0,0,0);
      uVar14 = ((long long (*)(void))device_info_text_width_get)();
      iVar15 = ((long long (*)(void))device_info_text_height_get_clamped)();
      iVar8 = ((long long (*)(void))device_info_text_width_get)();
      iVar7 = ((long long (*)(void))device_info_text_height_get_clamped)();
      gui_utf_draw(0,param_2 + 0x25,0,uVar14,iVar15 + 0x6d,iVar8 + 0x4c,iVar7 + 0x88,1,0,0,0,0);
    }
    iVar15 = ((long long (*)(void))get_device_info)();
    iVar15 = *(byte *)(*(int *)(iVar15 + 0xfec) + 0x5e) - 1;
    if (iVar15 != 0) {
      iVar15 = 1;
    }
    uVar14 = ((long long (*)(void))get_timestamp)();
    uVar9 = ((long long (*)(void))device_info_text_width_get)();
    iVar8 = ((long long (*)(void))device_info_text_height_get_clamped)();
    iVar7 = ((long long (*)(void))device_info_text_width_get)();
    iVar12 = ((long long (*)(void))device_info_text_height_get_clamped)();
    gui_clock_draw(uVar14,uVar9,iVar8 + 2,iVar7 + 0x4c,iVar12 + 0x1d,3,iVar15);
  }
  if (*DAT_0003ef5c == '\x01') {
    *DAT_0003ef5c = '\0';
    puVar5 = (undefined1 *)DAT_0003ef64;
    if (*(int *)(param_2 + 0xb1) == 0x1210) {
      if (2 < *DAT_0003ef60) {
        G1_LOG_ROUTE(*DAT_0003ef68 == 0, DAT_0003ef70,DAT_0003ef6c);
      }
      uVar32 = memset_bytes(DAT_0003ef74,0,0x1210);
      FUN_0007d376(DAT_0003ef78,(uint)(uVar32 >> 32),0xffffffff,0xffffffff);
      memcpy(DAT_0003ef74,DAT_0003ef7c,0x1210);
    }
    else {
      if (2 < *DAT_0003ef60) {
        if (*DAT_0003f28c == 0) {
          log_message(DAT_0003f298,DAT_0003f290);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      memset_bytes(DAT_0003f29c,0,0x1210);
      thunk_FUN_000723b8(DAT_0003f2a0,extraout_r1_00,0xffffffff,0xffffffff);
      decode_rle_byte_pairs(DAT_0003f2a4,*(undefined4 *)(param_2 + 0xb1),DAT_0003f29c);
    }
    uVar14 = DAT_0003ef78;
    *puVar5 = 1;
    FUN_0007d37a(uVar14);
  }
  *(undefined1 *)(iVar4 + 4) = 1;
  *(undefined1 *)(iVar4 + 5) = 0;
  *(undefined1 *)(iVar4 + 0x15) = 0;
  return;
}
