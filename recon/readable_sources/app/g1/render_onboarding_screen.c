#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000417f8 @ 0x000417f8
 * public-name: render_onboarding_screen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   render_onboarding_screen                 <= FUN_000417f8 @ 0x000417f8
 * address symbols (name @ address):
 *   rodata_aa600                             @ 0x000aa600
 *   rodata_aa604                             @ 0x000aa604
 *   rodata_aa608                             @ 0x000aa608
 *   rodata_aa60e                             @ 0x000aa60e
 *   rodata_f212c                             @ 0x000f212c
 *   rodata_f341d                             @ 0x000f341d
 *   rodata_f7a30                             @ 0x000f7a30
 *   rodata_f7b6f                             @ 0x000f7b6f
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 *   g_2001cdd0                               @ 0x2001cdd0
 *   onboarding_retry_counter                 @ 0x2001cdd1
 *   onboarding_attempt_counter               @ 0x2001cdd2
 */
/* Reconstructed FUN_000417f8 @ 0x417f8.
 * Semantic role: render the current onboarding/dashboard state.
 * Raw entry and every renamed callee/address remain back-mapped below.
 */
typedef unsigned char      undefined1;
typedef unsigned int       undefined4;
typedef unsigned long long undefined8;
typedef unsigned int       uint;
typedef unsigned char      byte;
typedef unsigned long long ulonglong;
typedef unsigned char      fw_bool;

/* Known callees (readable name <= raw symbol @ firmware address):
 * k_uptime_get_8 <= FUN_0007d382 @ 0x0007d382
 * get_device_info <= FUN_000167a8 @ 0x000167a8
 * device_info_text_width_get <= FUN_0007d3ee @ 0x0007d3ee
 * device_info_text_height_get_clamped <= FUN_0007d446 @ 0x0007d446
 * get_localized_weekday_name <= FUN_0007d4b2 @ 0x0007d4b2
 * strlen <= FUN_0000ef12 @ 0x0000ef12
 * memset_bytes <= FUN_00086c78 @ 0x00086c78
 * gui_reset_dynamic_bitmap_frame_state <= FUN_00043308 @ 0x00043308
 * gui_bmp_dynamic_bitmap_draw <= FUN_0004334c @ 0x0004334c
 * gui_bmp_bitmap_draw <= FUN_00043484 @ 0x00043484
 * gui_bmp_bitmap_draw_ex <= FUN_000435d4 @ 0x000435d4
 * gui_utf_draw <= FUN_00043e90 @ 0x00043e90
 */
extern unsigned long long k_uptime_get_8(void);
extern int  get_device_info(void);
extern int  get_ui_mode_flag_byte1(void);
extern int  device_info_text_width_get(void);
extern int  device_info_text_height_get_clamped(void);
extern int  get_localized_weekday_name(int);
extern int  strlen(void);
extern void memset_bytes(void*, int, int);
extern unsigned int gui_reset_dynamic_bitmap_frame_state(void);
extern void gui_bmp_dynamic_bitmap_draw(int,int,int,int,int,int,int);
extern int gui_bmp_bitmap_draw(unsigned int, int, int, int, int, int);
extern void gui_bmp_bitmap_draw_ex(int,int,int,void*,int);
extern void gui_utf_draw(int,int,int,int,int,int,int,int,int,int,int,int);
extern void send_event(int);

/* Onboarding globals; each definition retains its raw address. */
#define onboarding_render_retry_counter ((volatile unsigned char *)((unsigned long)&g_2001cdd0) /*=0x2001cdd0*/)
#define onboarding_secondary_reset_flag ((volatile unsigned char *)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/)
#define onboarding_retry_counter ((volatile unsigned char *)((unsigned long)&onboarding_retry_counter) /*=0x2001cdd1*/)
#define onboarding_attempt_counter ((volatile unsigned char *)((unsigned long)&onboarding_attempt_counter) /*=0x2001cdd2*/)

/* Onboarding text/assets; each definition retains its raw address. */
#define onboarding_text_aa608 ((unsigned int)((unsigned long)&rodata_aa608) /*=0xaa608*/)
#define onboarding_text_aa60e ((unsigned int)((unsigned long)&rodata_aa60e) /*=0xaa60e*/)
#define onboarding_text_f212c ((unsigned int)((unsigned long)&rodata_f212c) /*=0xf212c*/)
#define onboarding_text_f341d ((unsigned int)((unsigned long)&rodata_f341d) /*=0xf341d*/)
#define onboarding_text_aa604 ((unsigned int)((unsigned long)&rodata_aa604) /*=0xaa604*/)
#define onboarding_text_f7b6f ((unsigned int)((unsigned long)&rodata_f7b6f) /*=0xf7b6f*/)
#define onboarding_text_f7a30 ((unsigned int)((unsigned long)&rodata_f7a30) /*=0xf7a30*/)
#define onboarding_text_aa600 ((unsigned int)((unsigned long)&rodata_aa600) /*=0xaa600*/)

void render_onboarding_screen(void)

{
  uint uVar1;
  uint uVar2;
  volatile byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 uVar12;
  undefined1 uVar13;
  uint uVar14;
  fw_bool bVar15;
  undefined8 uVar16;
  undefined4 local_428;
  undefined1 auStack_424 [1024];

  local_428 = 0;
  memset_bytes(auStack_424,0,0x3fc);
  iVar4 = get_device_info();
  pbVar3 = onboarding_render_retry_counter;
  switch(*(undefined1 *)(*(int *)(iVar4 + 0x1014) + 2)) {
  case 0:
    uVar16 = k_uptime_get_8();
    iVar4 = get_device_info();
    uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
    uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
    uVar2 = (uint)((uint)uVar16 < uVar14);
    if (uVar1 == uVar2 && (uint)(4000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
      return;
    }
    iVar4 = get_device_info();
    *(char *)(*(int *)(iVar4 + 0x1014) + 3) = *(char *)(*(int *)(iVar4 + 0x1014) + 3) + '\x01';
    iVar4 = get_device_info();
    if (*(byte *)(*(int *)(iVar4 + 0x1014) + 3) < 2) {
      return;
    }
    iVar4 = get_device_info();
    uVar13 = 0;
    iVar5 = *(int *)(iVar4 + 0x1014);
    goto control_label_000418a6;
  case 3:
    iVar4 = get_device_info();
    iVar5 = get_device_info();
    pbVar3 = onboarding_render_retry_counter;
    *(undefined1 *)(*(int *)(iVar5 + 0x1014) + 3) = *(undefined1 *)(iVar4 + 0xee4);
    if (5 < *pbVar3) {
      return;
    }
    if (*pbVar3 != 0) {
      uVar16 = k_uptime_get_8();
      iVar4 = get_device_info();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if (uVar1 == uVar2 && (uint)(1000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
        return;
      }
    }
    uVar12 = 0x10;
    *pbVar3 = *pbVar3 + 1;
    goto control_label_000418d2;
  case 4:
    iVar4 = device_info_text_width_get();
    iVar5 = device_info_text_height_get_clamped();
    iVar5 = iVar5 + 0x70;
    iVar4 = iVar4 + 0x8a;
    goto control_label_00041938;
  case 5:
  case 0x14:
  case 0x15:
    iVar4 = get_device_info();
    iVar5 = get_device_info();
    *(undefined1 *)(*(int *)(iVar5 + 0x1014) + 3) = *(undefined1 *)(iVar4 + 0xee4);
    if (*onboarding_secondary_reset_flag == '\x01') {
      iVar4 = get_device_info();
      if ((*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x05') && (*onboarding_retry_counter == '\0')) {
        uVar16 = k_uptime_get_8();
        iVar4 = get_device_info();
        uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
        uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
        uVar2 = (uint)((uint)uVar16 < uVar14);
        if (uVar1 == uVar2 && (uint)(499 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
          return;
        }
      }
      iVar4 = get_ui_mode_flag_byte1();
      if (iVar4 == 6) {
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        gui_bmp_dynamic_bitmap_draw(2,iVar4 + 0x42,iVar5 + 0x70,0,0,0,0);
        uVar12 = get_localized_weekday_name(0x13);
        iVar4 = device_info_text_width_get();
        iVar6 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        iVar4 = iVar4 + 0x66;
      }
      else {
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        gui_bmp_dynamic_bitmap_draw(2,iVar4 + 0x82,iVar5 + 0x70,0,0,0,0);
        uVar12 = get_localized_weekday_name(0x13);
        iVar4 = device_info_text_width_get();
        iVar6 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        iVar4 = iVar4 + 0xa6;
      }
      gui_utf_draw(0,uVar12,0,iVar4,iVar6 + 0x6d,iVar5 + 0x240,iVar7 + 0x88,1,0,0,0,0);
      return;
    }
    if (*onboarding_secondary_reset_flag != '\x02') {
      return;
    }
    uVar16 = k_uptime_get_8();
    iVar4 = get_device_info();
    uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
    uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
    uVar2 = (uint)((uint)uVar16 < uVar14);
    if ((uVar1 != uVar2 || uVar1 - uVar2 < (uint)(2000 < (uint)uVar16 - uVar14)) ||
       (*onboarding_retry_counter != '\0')) {
      if (*onboarding_attempt_counter == '\0') {
        *onboarding_attempt_counter = '\x01';
        uVar12 = get_localized_weekday_name(0x14);
        uVar8 = device_info_text_width_get();
        uVar9 = device_info_text_height_get_clamped();
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        get_localized_weekday_name(0x14);
        uVar10 = strlen();
        gui_utf_draw(0,uVar12,3,uVar8,uVar9,iVar4 + 0x76,iVar5 + 0x1b,1,uVar10,0,0,0);
        uVar12 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar6 = device_info_text_height_get_clamped();
        gui_utf_draw(0,onboarding_text_aa608,1,uVar12,iVar4 + 0x1b,iVar5 + 0x68,iVar6 + 0x42,1,5,0,0,0);
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw_ex(0x29,iVar4 + 0xa6,iVar5 + 4,&local_428,0x55);
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar6 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        gui_utf_draw(0,onboarding_text_aa60e,3,iVar4 + 0xc2,iVar5 + 3,iVar6 + 0xea,iVar7 + 0x1e,1,2,0,0,0);
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar6 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        gui_utf_draw(0,onboarding_text_f212c,3,iVar4 + 0xde,iVar5 + 3,iVar6 + 0xec,iVar7 + 0x1e,1,1,0,0,0);
        iVar4 = get_device_info();
        bVar15 = *(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x05';
        if (bVar15) {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          gui_bmp_bitmap_draw_ex(0x3c,iVar4 + 0xa6,iVar5 + 0x23,&local_428,0x55);
          iVar6 = device_info_text_width_get();
          iVar7 = device_info_text_height_get_clamped();
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          uVar12 = onboarding_text_f7a30;
        }
        else {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          gui_bmp_bitmap_draw(0x3c,iVar4 + 0xa6,iVar5 + 0x23,0,0,0);
          iVar6 = device_info_text_width_get();
          iVar7 = device_info_text_height_get_clamped();
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          uVar12 = onboarding_text_f341d;
        }
        gui_utf_draw(0,uVar12,3,iVar6 + 0xc2,iVar7 + 0x23,iVar4 + 0xd6,iVar5 + 0x3e,1,bVar15,0,0,0);
        uVar12 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw_ex(0x39,uVar12,iVar4 + 0x51,&local_428,0x55);
        uVar12 = get_localized_weekday_name(0x16);
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar6 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        get_localized_weekday_name(0x16);
        uVar8 = strlen();
        gui_utf_draw(0,uVar12,0,iVar4 + 0x1c,iVar5 + 0x51,iVar6 + 0xf2,iVar7 + 0x6c,1,uVar8,0,0,0);
        uVar12 = get_localized_weekday_name(0x15);
        uVar8 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar6 = device_info_text_height_get_clamped();
        get_localized_weekday_name(0x15);
        uVar9 = strlen();
        gui_utf_draw(0,uVar12,0,uVar8,iVar4 + 0x6d,iVar5 + 0xf2,iVar6 + 0x88,1,uVar9,0,0,0);
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x14') {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          gui_bmp_bitmap_draw(0x3b,iVar4 + 0x108,iVar5 + 1,0,0,0);
          uVar12 = get_localized_weekday_name(0x17);
          iVar4 = device_info_text_width_get();
          uVar8 = device_info_text_height_get_clamped();
          iVar5 = device_info_text_width_get();
          iVar6 = device_info_text_height_get_clamped();
          gui_utf_draw(0,uVar12,0,iVar4 + 0x126,uVar8,iVar5 + 0x202,iVar6 + 0x1b,1,0,0,0,0);
          iVar7 = device_info_text_width_get();
          iVar6 = device_info_text_height_get_clamped();
          iVar5 = device_info_text_width_get();
          iVar4 = device_info_text_height_get_clamped();
          uVar8 = 0;
          uVar12 = onboarding_text_aa604;
        }
        else {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          gui_bmp_bitmap_draw_ex(0x3b,iVar4 + 0x108,iVar5 + 1,&local_428,0x55);
          uVar12 = get_localized_weekday_name(0x17);
          iVar4 = device_info_text_width_get();
          uVar8 = device_info_text_height_get_clamped();
          iVar5 = device_info_text_width_get();
          iVar6 = device_info_text_height_get_clamped();
          get_localized_weekday_name(0x17);
          uVar9 = strlen();
          gui_utf_draw(0,uVar12,0,iVar4 + 0x126,uVar8,iVar5 + 0x202,iVar6 + 0x1b,1,uVar9,0,0,0);
          iVar4 = get_device_info();
          uVar12 = onboarding_text_aa604;
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x15') {
            uVar12 = onboarding_text_aa600;
          }
          iVar7 = device_info_text_width_get();
          iVar6 = device_info_text_height_get_clamped();
          iVar5 = device_info_text_width_get();
          iVar4 = device_info_text_height_get_clamped();
          uVar8 = 3;
        }
        gui_utf_draw(0,uVar12,3,iVar7 + 0x210,iVar6 + 1,iVar5 + 0x234,iVar4 + 0x1c,1,uVar8,0,0,0);
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x15') {
          uVar12 = 0xe;
        }
        else {
          uVar12 = 0x18;
        }
        uVar12 = get_localized_weekday_name(uVar12);
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar6 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        iVar11 = get_device_info();
        if (*(char *)(*(int *)(iVar11 + 0x1014) + 2) == '\x15') {
          uVar8 = 0xe;
        }
        else {
          uVar8 = 0x18;
        }
        get_localized_weekday_name(uVar8);
        uVar8 = strlen();
        gui_utf_draw(0,uVar12,0,iVar4 + 0x108,iVar5 + 0x1b,iVar6 + 0x232,iVar7 + 0x87,4,uVar8,0,0,0)
        ;
        iVar4 = device_info_text_width_get();
        uVar12 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw_ex(0x4e,iVar4 + 0xfc,uVar12,&local_428,0x55);
        iVar4 = device_info_text_width_get();
        uVar12 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw_ex(0x4f,iVar4 + 0x23e,uVar12,&local_428,0x55);
        uVar12 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        iVar5 = device_info_text_width_get();
        iVar6 = device_info_text_height_get_clamped();
        gui_utf_draw(0,onboarding_text_f7b6f,0,uVar12,iVar4 + 0x6d,iVar5 + 0x240,iVar6 + 0x88,1,0,0,0,0);
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x05') {
          iVar4 = get_ui_mode_flag_byte1();
          if (iVar4 == 6) {
            uVar12 = get_localized_weekday_name(9);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar6 = device_info_text_width_get();
            iVar7 = device_info_text_height_get_clamped();
            gui_utf_draw(0,uVar12,0,iVar4 + 0x5c,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar4 = iVar4 + 0xae;
          }
          else {
            uVar12 = get_localized_weekday_name(9);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar6 = device_info_text_width_get();
            iVar7 = device_info_text_height_get_clamped();
            gui_utf_draw(0,uVar12,0,iVar4 + 0x6a,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar4 = iVar4 + 0xca;
          }
          uVar12 = 0x7a;
        }
        else {
          iVar4 = get_device_info();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x14') {
            iVar4 = get_device_info();
            if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x15') {
              iVar4 = get_ui_mode_flag_byte1();
              if (iVar4 == 6) {
                uVar12 = get_localized_weekday_name(0xf);
                iVar4 = device_info_text_width_get();
                iVar5 = device_info_text_height_get_clamped();
                iVar6 = device_info_text_width_get();
                iVar7 = device_info_text_height_get_clamped();
                iVar4 = iVar4 + 100;
              }
              else {
                uVar12 = get_localized_weekday_name(0xf);
                iVar4 = device_info_text_width_get();
                iVar5 = device_info_text_height_get_clamped();
                iVar6 = device_info_text_width_get();
                iVar7 = device_info_text_height_get_clamped();
                iVar4 = iVar4 + 0x92;
              }
              gui_utf_draw(0,uVar12,0,iVar4,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
            }
            goto control_label_00041f3a;
          }
          uVar12 = get_localized_weekday_name(0xb);
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar6 = device_info_text_width_get();
          iVar7 = device_info_text_height_get_clamped();
          gui_utf_draw(0,uVar12,0,iVar4 + 0x54,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
          iVar4 = get_ui_mode_flag_byte1();
          if (iVar4 == 6) {
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar4 = iVar4 + 0xaa;
          }
          else {
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar4 = iVar4 + 0xb2;
          }
          uVar12 = 0x7b;
        }
        gui_bmp_bitmap_draw(uVar12,iVar4,iVar5 + 0x87,0,0,0);
      }
control_label_00041f3a:
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x05') {
        iVar4 = get_ui_mode_flag_byte1();
        if (iVar4 == 6) {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x38;
        }
        else {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x46;
        }
      }
      else {
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x14') {
          iVar4 = get_device_info();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x15') goto control_label_00041f76;
          iVar4 = get_ui_mode_flag_byte1();
          if (iVar4 == 6) {
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar5 = iVar5 + 0x70;
            iVar4 = iVar4 + 0x40;
          }
          else {
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar5 = iVar5 + 0x70;
            iVar4 = iVar4 + 0x6e;
          }
          goto control_label_000422ba;
        }
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x30;
      }
control_label_00041f70:
      uVar12 = 0xb;
control_label_00041f72:
      gui_bmp_dynamic_bitmap_draw(uVar12,iVar4,iVar5,0,0,0,0);
    }
control_label_00041f76:
    iVar4 = get_device_info();
    if (*(char *)(*(int *)(iVar4 + 0x1014) + 3) == '\x01') {
      *onboarding_retry_counter = 1;
    }
    break;
  case 6:
  case 0x13:
    iVar4 = get_device_info();
    iVar5 = get_device_info();
    *(undefined1 *)(*(int *)(iVar5 + 0x1014) + 3) = *(undefined1 *)(iVar4 + 0xee4);
    if (*onboarding_secondary_reset_flag != '\x01') {
      if (*onboarding_secondary_reset_flag != '\x02') {
        return;
      }
      uVar16 = k_uptime_get_8();
      iVar4 = get_device_info();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if ((uVar1 == uVar2 && (uint)(2000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) &&
         (*onboarding_retry_counter == '\0')) goto control_label_00041f76;
      if (*onboarding_attempt_counter == '\0') {
        *onboarding_attempt_counter = '\x01';
        iVar4 = get_device_info();
        if (-1 < (int)((uint)*(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) << 0x1d)) {
          send_event(0x15);
          iVar4 = get_device_info();
          *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) =
               *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) | 4;
        }
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          gui_bmp_bitmap_draw_ex(0x3c,iVar4 + 0x212,iVar5 + 4,&local_428,0x55);
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar6 = device_info_text_width_get();
          iVar7 = device_info_text_height_get_clamped();
          uVar8 = 1;
          uVar12 = onboarding_text_f341d;
control_label_00042560:
          gui_utf_draw(0,uVar12,3,iVar4 + 0x22e,iVar5 + 3,iVar6 + 0x23e,iVar7 + 0x1e,1,uVar8,0,0,0);
        }
        else {
          iVar4 = get_device_info();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            gui_bmp_bitmap_draw(0x3c,iVar4 + 0x212,iVar5 + 4,0,0,0);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar6 = device_info_text_width_get();
            iVar7 = device_info_text_height_get_clamped();
            uVar8 = 0;
            uVar12 = onboarding_text_f7a30;
            goto control_label_00042560;
          }
        }
        uVar12 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw_ex(0x38,uVar12,iVar4 + 4,&local_428,0x55);
        uVar12 = get_localized_weekday_name(0x1a);
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar6 = device_info_text_width_get();
        iVar7 = device_info_text_height_get_clamped();
        get_localized_weekday_name(0x1a);
        uVar8 = strlen();
        gui_utf_draw(0,uVar12,0,iVar4 + 0x24,iVar5 + 3,iVar6 + 0x150,iVar7 + 0x1e,1,uVar8,0,0,0);
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
          uVar12 = get_localized_weekday_name(0x1c);
          uVar8 = device_info_text_width_get();
          iVar4 = device_info_text_height_get_clamped();
          iVar5 = device_info_text_width_get();
          iVar6 = device_info_text_height_get_clamped();
          uVar9 = 0x1c;
control_label_00042606:
          get_localized_weekday_name(uVar9);
          uVar9 = strlen();
          gui_utf_draw(0,uVar12,0,uVar8,iVar4 + 0x37,iVar5 + 0x240,iVar6 + 0x6d,2,uVar9,0,0,0);
        }
        else {
          iVar4 = get_device_info();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
            uVar12 = get_localized_weekday_name(0xc);
            uVar8 = device_info_text_width_get();
            iVar4 = device_info_text_height_get_clamped();
            iVar5 = device_info_text_width_get();
            iVar6 = device_info_text_height_get_clamped();
            uVar9 = 0xc;
            goto control_label_00042606;
          }
        }
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
          iVar4 = get_ui_mode_flag_byte1();
          if (iVar4 == 6) {
            uVar12 = get_localized_weekday_name(0x10);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar6 = device_info_text_width_get();
            iVar7 = device_info_text_height_get_clamped();
            iVar4 = iVar4 + 0x34;
          }
          else {
            uVar12 = get_localized_weekday_name(0x10);
            iVar4 = device_info_text_width_get();
            iVar5 = device_info_text_height_get_clamped();
            iVar6 = device_info_text_width_get();
            iVar7 = device_info_text_height_get_clamped();
            iVar4 = iVar4 + 0x72;
          }
          gui_utf_draw(0,uVar12,0,iVar4,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
        }
        else {
          iVar4 = get_device_info();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
            iVar4 = get_ui_mode_flag_byte1();
            if (iVar4 == 6) {
              uVar12 = get_localized_weekday_name(10);
              iVar4 = device_info_text_width_get();
              iVar5 = device_info_text_height_get_clamped();
              iVar6 = device_info_text_width_get();
              iVar7 = device_info_text_height_get_clamped();
              gui_utf_draw(0,uVar12,0,iVar4 + 0x8a,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0
                          );
              iVar4 = device_info_text_width_get();
              iVar5 = device_info_text_height_get_clamped();
              iVar4 = iVar4 + 0xdc;
            }
            else {
              uVar12 = get_localized_weekday_name(10);
              iVar4 = device_info_text_width_get();
              iVar5 = device_info_text_height_get_clamped();
              iVar6 = device_info_text_width_get();
              iVar7 = device_info_text_height_get_clamped();
              gui_utf_draw(0,uVar12,0,iVar4 + 0x94,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0
                          );
              iVar4 = device_info_text_width_get();
              iVar5 = device_info_text_height_get_clamped();
              iVar4 = iVar4 + 0xf4;
            }
            gui_bmp_bitmap_draw(0x7a,iVar4,iVar5 + 0x87,0,0,0);
          }
        }
      }
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
        iVar4 = get_ui_mode_flag_byte1();
        if (iVar4 == 6) {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x10;
        }
        else {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x4e;
        }
control_label_000422ba:
        uVar12 = 3;
        goto control_label_00041f72;
      }
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
        iVar4 = get_ui_mode_flag_byte1();
        if (iVar4 == 6) {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x66;
        }
        else {
          iVar4 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x70;
        }
        goto control_label_00041f70;
      }
      goto control_label_00041f76;
    }
    iVar4 = get_device_info();
    if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
      uVar16 = k_uptime_get_8();
      iVar4 = get_device_info();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if (uVar1 == uVar2 && (uint)(2000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
        return;
      }
      if (*onboarding_attempt_counter == '\0') {
        *onboarding_attempt_counter = '\x01';
        gui_reset_dynamic_bitmap_frame_state();
        uVar12 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw_ex(0x38,uVar12,iVar4 + 0x37,&local_428,0x55);
        iVar4 = get_ui_mode_flag_byte1();
        if (iVar4 == 6) {
          uVar12 = get_localized_weekday_name(0x19);
          iVar4 = device_info_text_width_get();
          iVar7 = device_info_text_height_get_clamped();
          iVar6 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar4 = iVar4 + 0x34;
        }
        else {
          uVar12 = get_localized_weekday_name(0x19);
          iVar4 = device_info_text_width_get();
          iVar7 = device_info_text_height_get_clamped();
          iVar6 = device_info_text_width_get();
          iVar5 = device_info_text_height_get_clamped();
          iVar4 = iVar4 + 0x8c;
        }
        gui_utf_draw(0,uVar12,0,iVar4,iVar7 + 0x6d,iVar6 + 0x240,iVar5 + 0x88,1,0,0,0,0);
      }
      iVar4 = get_ui_mode_flag_byte1();
      if (iVar4 == 6) {
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x10;
      }
      else {
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x68;
      }
    }
    else {
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x13') {
        return;
      }
      iVar4 = get_ui_mode_flag_byte1();
      if (iVar4 == 6) {
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x74;
      }
      else {
        iVar4 = device_info_text_width_get();
        iVar5 = device_info_text_height_get_clamped();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x82;
      }
    }
    uVar12 = 2;
    goto control_label_000423d0;
  case 8:
    iVar4 = get_ui_mode_flag_byte1();
    if (iVar4 == 6) {
      iVar4 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar5 = iVar5 + 0x70;
      iVar4 = iVar4 + 0x88;
    }
    else {
      iVar4 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar5 = iVar5 + 0x70;
      iVar4 = iVar4 + 0x66;
    }
control_label_00041938:
    uVar12 = 0xc;
control_label_000423d0:
    gui_bmp_dynamic_bitmap_draw(uVar12,iVar4,iVar5,0,0,0,0);
    break;
  case 0xf:
  case 0x11:
    iVar4 = get_device_info();
    iVar5 = get_device_info();
    iVar5 = *(int *)(iVar5 + 0x1014);
    uVar13 = *(undefined1 *)(iVar4 + 0xee4);
control_label_000418a6:
    *(undefined1 *)(iVar5 + 3) = uVar13;
    break;
  case 0x16:
    uVar16 = k_uptime_get_8();
    iVar4 = get_device_info();
    uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
    uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
    uVar2 = (uint)((uint)uVar16 < uVar14);
    if (uVar1 != uVar2 || uVar1 - uVar2 < (uint)(4000 < (uint)uVar16 - uVar14)) {
      iVar4 = get_device_info();
      *(undefined1 *)(*(int *)(iVar4 + 0x1014) + 2) = 5;
    }
    break;
  case 0x17:
    if (5 < *onboarding_render_retry_counter) {
      return;
    }
    if (*onboarding_render_retry_counter != 0) {
      uVar16 = k_uptime_get_8();
      iVar4 = get_device_info();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if (uVar1 == uVar2 && (uint)(1000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
        return;
      }
    }
    uVar12 = 0x14;
    *pbVar3 = *pbVar3 + 1;
control_label_000418d2:
    send_event(uVar12);
    uVar16 = k_uptime_get_8();
    iVar4 = get_device_info();
    *(undefined8 *)(*(int *)(iVar4 + 0x1014) + 4) = uVar16;
  }
  return;
}
