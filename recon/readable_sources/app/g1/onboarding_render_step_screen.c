#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00040794 @ 0x00040794
 * public-name: onboarding_render_step_screen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   onboarding_render_step_screen            <= FUN_00040794 @ 0x00040794
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   get_localized_string_ptr                 <= FUN_000456fc @ 0x000456fc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   get_localized_weekday_name               <= FUN_0007d4b2 @ 0x0007d4b2
 * address symbols (name @ address):
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_aa600                             @ 0x000aa600
 *   rodata_aa604                             @ 0x000aa604
 *   rodata_aa608                             @ 0x000aa608
 *   rodata_aa60e                             @ 0x000aa60e
 *   rodata_aae20                             @ 0x000aae20
 *   rodata_f212c                             @ 0x000f212c
 *   rodata_f341d                             @ 0x000f341d
 *   rodata_f3449                             @ 0x000f3449
 *   rodata_f7a30                             @ 0x000f7a30
 *   g_200034f3                               @ 0x200034f3
 *   g_onboarding_step_retry_cnt              @ 0x20004bf0
 *   g_20009ff4                               @ 0x20009ff4
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 *   g_2001cdd0                               @ 0x2001cdd0
 *   onboarding_retry_counter                 @ 0x2001cdd1
 *   onboarding_attempt_counter               @ 0x2001cdd2
 *   onboarding_watchdog_active_flag          @ 0x2001cdd3
 */
/* Reconstructed FUN_00040794 @ 0x40794  (parity: 4/300 trials, PROVEN) */
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned int undefined4;
typedef unsigned int uint;

extern int get_device_info(void);
extern int get_ui_mode_flag_byte1(void);
extern void gui_screen_clear(void);
extern void gui_canvas_flags_set_bit1(void);
extern void gui_canvas_flags_clear_bit1(void);
extern void gui_bmp_bitmap_draw(int,int,int,int,int,int);
extern void gui_utf_draw(int,int,int,int,int,int,int,int,int,int,int,int);
extern int get_localized_string_ptr(int,int);
extern void reflash_fb_data_to_lcd(int,int,int,int,int,int);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern int get_localized_weekday_name(int);
extern void send_event(int);

#define B(a) (*(volatile byte*)(a))

void onboarding_render_step_screen(void)
{
  byte bVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined1 uVar10;
  uint uVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 local_30;
  undefined4 uStack_2c;

  iVar4 = get_device_info();
  if (B(((unsigned long)&onboarding_watchdog_active_flag) /*=0x2001cdd3*/) == '\0') {
    return;
  }
  B(((unsigned long)&onboarding_watchdog_active_flag) /*=0x2001cdd3*/) = '\0';
  gui_screen_clear();
  iVar5 = get_device_info();
  if ((((((*(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\0') &&
         (iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\n')) &&
        (iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\v')) &&
       ((iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x05' &&
        (iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x06')))) &&
      ((iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x13' &&
       ((iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x14' &&
        (iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x15')))))) &&
     ((iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x0e' &&
      ((((iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x0f' &&
         (iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x10')) &&
        (iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x11')) &&
       ((iVar5 = get_device_info(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x03' ||
        (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) != 2)))))))) {
    iVar5 = get_device_info();
    iVar12 = *(int *)(iVar5 + 0x1014);
    uVar6 = device_info_text_width_get();
    iVar5 = device_info_text_height_get_clamped();
    iVar7 = device_info_text_width_get();
    iVar8 = device_info_text_height_get_clamped();
    gui_utf_draw(0,iVar12 + 0x1b,3,uVar6,iVar5 + 0x37,iVar7 + 0x28,iVar8 + 0x52,4,0,0,0,0);
  }
  iVar5 = get_device_info();
  switch(*(undefined1 *)(*(int *)(iVar5 + 0x1014) + 2)) {
  case 0:
    gui_canvas_flags_clear_bit1();
    piVar2 = (int*)((unsigned long)&g_20009ff4) /*=0x20009ff4*/;
    *(int*)((unsigned long)&g_20009ff4) /*=0x20009ff4*/ = 0;
    while (*piVar2 < 8) {
      uVar6 = device_info_text_width_get();
      uVar11 = 0;
      iVar5 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x16,uVar6,iVar5 + 0x38,0,0,0);
      uVar6 = get_localized_string_ptr(B(((unsigned long)&g_200034f3) /*=0x200034f3*/ + (uint)B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/)),1);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar5 + 0x40,iVar7 + 0x37,iVar8 + 0x240,iVar12 + 0x88,4,0,0,0,0);
      puVar3 = (undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
      iVar5 = *piVar2;
      local_30 = *(undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
      do {
        uStack_2c = puVar3[1];
        iVar7 = 0;
        do {
          iVar8 = *(int *)(iVar4 + 0xb90 + uVar11 * 4);
          bVar1 = *(byte *)(iVar8 + iVar7);
          if (bVar1 != 0) {
            *(byte *)(iVar8 + iVar7) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                   (uVar11 % 0x1a) * 0xa00 + ((unsigned long)&rodata_aae20) /*=0xaae20*/ + iVar7);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x140);
        uVar11 = uVar11 + 1;
      } while (uVar11 != 199);
      *piVar2 = iVar5 + 1;
      iVar5 = get_device_info();
      uVar6 = *(undefined4 *)(iVar5 + 0xeb4);
      iVar5 = get_device_info();
      reflash_fb_data_to_lcd(uVar6,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x280,199);
    }
    goto control_label_00040928;
  case 1:
    uVar6 = get_localized_weekday_name(6);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x8c;
    break;
  case 2:
    uVar6 = get_localized_weekday_name(0x20);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x80;
    break;
  case 3:
  case 5:
  case 0x14:
  case 0x15:
    if (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) == '\x01') {
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x03') {
        iVar4 = get_device_info();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x15') goto switchD_000408e4_caseD_a;
        B(((unsigned long)&g_2001cdd0) /*=0x2001cdd0*/) = 0;
        iVar4 = get_device_info();
        if ((*(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) & 3) != 1) goto switchD_000408e4_caseD_a;
        send_event(0x14);
        iVar4 = get_device_info();
        *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) | 2;
        iVar4 = get_device_info();
        uVar10 = 0x17;
        iVar4 = *(int *)(iVar4 + 0x1014);
control_label_00040c1c:
        *(undefined1 *)(iVar4 + 2) = uVar10;
        goto switchD_000408e4_caseD_a;
      }
      B(((unsigned long)&g_2001cdd0) /*=0x2001cdd0*/) = 0;
      uVar6 = get_localized_weekday_name(8);
      iVar8 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar7 = iVar7 + 0x88;
      uVar13 = 4;
      iVar8 = iVar8 + 0x8c;
      goto control_label_00040bc6;
    }
    if (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) != '\x02') goto switchD_000408e4_caseD_a;
    iVar5 = get_device_info();
    if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') &&
       (iVar5 = get_device_info(), -1 < (int)((uint)*(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) << 0x1f)
       )) {
      send_event(0x13);
      iVar5 = get_device_info();
      *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) | 1;
    }
    if (B(((unsigned long)&onboarding_retry_counter) /*=0x2001cdd1*/) != '\0') {
control_label_00040c64:
      B(((unsigned long)&onboarding_attempt_counter) /*=0x2001cdd2*/) = 0;
      goto switchD_000408e4_caseD_a;
    }
    iVar5 = get_device_info();
    if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x15') ||
       (*(char *)(((unsigned long)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/ + 0x10) == '\x01')) {
      gui_canvas_flags_clear_bit1();
    }
    piVar2 = (int*)((unsigned long)&g_20009ff4) /*=0x20009ff4*/;
    *(int*)((unsigned long)&g_20009ff4) /*=0x20009ff4*/ = 0;
    while (*piVar2 < 8) {
      uVar6 = get_localized_weekday_name(0x14);
      uVar13 = device_info_text_width_get();
      uVar9 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,3,uVar13,uVar9,iVar5 + 0x76,iVar7 + 0x1b,1,0,0,0,0);
      uVar6 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar7 = device_info_text_width_get();
      iVar8 = device_info_text_height_get_clamped();
      gui_utf_draw(0,((unsigned long)&rodata_aa608) /*=0xaa608*/,1,uVar6,iVar5 + 0x1b,iVar7 + 0x68,iVar8 + 0x42,1,0,0,0,0);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x29,iVar5 + 0xa6,iVar7 + 4,0,0,0);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,((unsigned long)&rodata_aa60e) /*=0xaa60e*/,3,iVar5 + 0xc2,iVar7 + 3,iVar8 + 0xea,iVar12 + 0x1e,1,0,0,0,0);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,((unsigned long)&rodata_f212c) /*=0xf212c*/,3,iVar5 + 0xde,iVar7 + 3,iVar8 + 0xec,iVar12 + 0x1e,1,0,0,0,0);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x3c,iVar5 + 0xa6,iVar7 + 0x23,0,0,0);
      iVar5 = get_device_info();
      uVar6 = ((unsigned long)&rodata_f341d) /*=0xf341d*/;
      if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x05') &&
         (iVar5 = get_device_info(), uVar6 = ((unsigned long)&rodata_f7a30) /*=0xf7a30*/,
         *(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x03')) {
        uVar6 = ((unsigned long)&rodata_f3449) /*=0xf3449*/;
      }
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,3,iVar5 + 0xc2,iVar7 + 0x23,iVar8 + 0xd6,iVar12 + 0x3e,1,0,0,0,0);
      uVar6 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x39,uVar6,iVar5 + 0x51,0,0,0);
      uVar6 = get_localized_weekday_name(0x16);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar5 + 0x1c,iVar7 + 0x51,iVar8 + 0xf2,iVar12 + 0x6c,1,0,0,0,0);
      uVar6 = get_localized_weekday_name(0x15);
      uVar13 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar7 = device_info_text_width_get();
      iVar8 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,uVar13,iVar5 + 0x6d,iVar7 + 0xf2,iVar8 + 0x88,1,0,0,0,0);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x3b,iVar5 + 0x108,iVar7 + 1,0,0,0);
      uVar6 = get_localized_weekday_name(0x17);
      iVar5 = device_info_text_width_get();
      uVar13 = device_info_text_height_get_clamped();
      iVar7 = device_info_text_width_get();
      iVar8 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar5 + 0x126,uVar13,iVar7 + 0x202,iVar8 + 0x1b,1,0,0,0,0);
      iVar5 = get_device_info();
      uVar6 = ((unsigned long)&rodata_aa604) /*=0xaa604*/;
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') {
        uVar6 = ((unsigned long)&rodata_aa600) /*=0xaa600*/;
      }
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,3,iVar5 + 0x210,iVar7 + 1,iVar8 + 0x234,iVar12 + 0x1c,1,0,0,0,0);
      iVar5 = get_device_info();
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') {
        uVar6 = 0xe;
      }
      else {
        uVar6 = 0x18;
      }
      uVar6 = get_localized_weekday_name(uVar6);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar5 + 0x108,iVar7 + 0x1b,iVar8 + 0x232,iVar12 + 0x87,4,0,0,0,0);
      iVar5 = device_info_text_width_get();
      uVar6 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x4e,iVar5 + 0xfc,uVar6,0,0,0);
      iVar5 = device_info_text_width_get();
      uVar6 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x4f,iVar5 + 0x23e,uVar6,0,0,0);
      iVar5 = get_device_info();
      puVar3 = (undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
      if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') &&
         (*(char *)(((unsigned long)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/ + 0x10) != '\x01')) break;
      uVar11 = 0;
      iVar5 = *piVar2;
      local_30 = *(undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
      do {
        uStack_2c = puVar3[1];
        iVar7 = 0;
        do {
          iVar8 = *(int *)(iVar4 + 0xb90 + uVar11 * 4);
          bVar1 = *(byte *)(iVar8 + iVar7);
          if (bVar1 != 0) {
            *(byte *)(iVar8 + iVar7) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                   (uVar11 % 0x1a) * 0xa00 + ((unsigned long)&rodata_aae20) /*=0xaae20*/ + iVar7);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x140);
        uVar11 = uVar11 + 1;
      } while (uVar11 != 199);
      *piVar2 = iVar5 + 1;
      iVar5 = get_device_info();
      uVar6 = *(undefined4 *)(iVar5 + 0xeb4);
      iVar5 = get_device_info();
      reflash_fb_data_to_lcd(uVar6,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x280,199);
    }
    goto control_label_00040928;
  case 4:
    uVar6 = get_localized_weekday_name(7);
    iVar4 = device_info_text_width_get();
    iVar5 = device_info_text_height_get_clamped();
    iVar7 = device_info_text_width_get();
    iVar8 = device_info_text_height_get_clamped();
    gui_utf_draw(0,uVar6,0,iVar4 + 0xd2,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x52,1,0,0,0,0);
    uVar6 = get_localized_weekday_name(0x1f);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x6d;
    iVar8 = iVar8 + 0xae;
    goto control_label_00040b66;
  case 6:
  case 0x13:
    if (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) == '\x01') {
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
        uVar6 = device_info_text_width_get();
        iVar4 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw(0x38,uVar6,iVar4 + 0x37,0,0,0);
        iVar4 = get_device_info();
        if ((*(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) & 0xc) != 4) goto switchD_000408e4_caseD_a;
        send_event(0x16);
        iVar4 = get_device_info();
        *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) | 8;
        iVar4 = get_device_info();
        uVar10 = 5;
        iVar4 = *(int *)(iVar4 + 0x1014);
        goto control_label_00040c1c;
      }
      iVar4 = get_device_info();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x13') goto switchD_000408e4_caseD_a;
      uVar6 = get_localized_weekday_name(0x22);
      iVar8 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar7 = iVar7 + 0x88;
      iVar4 = iVar4 + 0x6d;
      iVar8 = iVar8 + 0xa6;
      uVar13 = 1;
      goto control_label_000411c8;
    }
    if (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) != '\x02') goto switchD_000408e4_caseD_a;
    iVar5 = get_device_info();
    if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x06') {
      iVar5 = get_device_info();
      if (-1 < (int)((uint)*(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) << 0x1d)) {
        send_event(0x15);
        iVar5 = get_device_info();
        *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) | 4;
      }
    }
    else {
      iVar5 = get_device_info();
      if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x13') && (B(((unsigned long)&onboarding_retry_counter) /*=0x2001cdd1*/) != '\0'))
      goto control_label_00040c64;
    }
    gui_canvas_flags_clear_bit1();
    piVar2 = (int*)((unsigned long)&g_20009ff4) /*=0x20009ff4*/;
    *(int*)((unsigned long)&g_20009ff4) /*=0x20009ff4*/ = 0;
    while (*piVar2 < 8) {
      iVar5 = device_info_text_width_get();
      uVar11 = 0;
      iVar7 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x3c,iVar5 + 0x212,iVar7 + 4,0,0,0);
      iVar5 = get_device_info();
      uVar6 = ((unsigned long)&rodata_f7a30) /*=0xf7a30*/;
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x06') {
        uVar6 = ((unsigned long)&rodata_f341d) /*=0xf341d*/;
      }
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,3,iVar5 + 0x22e,iVar7 + 3,iVar8 + 0x23e,iVar12 + 0x1e,1,0,0,0,0);
      uVar6 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x38,uVar6,iVar5 + 4,0,0,0);
      uVar6 = get_localized_weekday_name(0x1a);
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar8 = device_info_text_width_get();
      iVar12 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar5 + 0x24,iVar7 + 3,iVar8 + 0x150,iVar12 + 0x1e,1,0,0,0,0);
      iVar5 = get_device_info();
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x06') {
        uVar6 = 0x1c;
      }
      else {
        uVar6 = 0xc;
      }
      uVar6 = get_localized_weekday_name(uVar6);
      uVar13 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar7 = device_info_text_width_get();
      iVar8 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,uVar13,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x6d,2,0,0,0,0);
      puVar3 = (undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
      iVar5 = *piVar2;
      local_30 = *(undefined4*)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
      do {
        uStack_2c = puVar3[1];
        iVar7 = 0;
        do {
          iVar8 = *(int *)(iVar4 + 0xb90 + uVar11 * 4);
          bVar1 = *(byte *)(iVar8 + iVar7);
          if (bVar1 != 0) {
            *(byte *)(iVar8 + iVar7) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                   (uVar11 % 0x1a) * 0xa00 + ((unsigned long)&rodata_aae20) /*=0xaae20*/ + iVar7);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x140);
        uVar11 = uVar11 + 1;
      } while (uVar11 != 199);
      *piVar2 = iVar5 + 1;
      iVar5 = get_device_info();
      uVar6 = *(undefined4 *)(iVar5 + 0xeb4);
      iVar5 = get_device_info();
      reflash_fb_data_to_lcd(uVar6,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x280,199);
    }
control_label_00040928:
    gui_canvas_flags_set_bit1();
    goto switchD_000408e4_caseD_a;
  case 7:
  case 9:
  case 0xc:
  case 0xd:
    uVar6 = get_localized_weekday_name(0x21);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x72;
    break;
  case 8:
    iVar4 = get_ui_mode_flag_byte1();
    if (iVar4 == 6) {
      uVar6 = get_localized_weekday_name(7);
      iVar4 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar7 = device_info_text_width_get();
      iVar8 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar4 + 0xc6,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x52,1,0,0,0,0);
      uVar6 = get_localized_weekday_name(0x1f);
      iVar8 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar5 = iVar5 + 0x240;
      iVar7 = iVar7 + 0x88;
      iVar4 = iVar4 + 0x6d;
      iVar8 = iVar8 + 0xac;
    }
    else {
      uVar6 = get_localized_weekday_name(7);
      iVar4 = device_info_text_width_get();
      iVar5 = device_info_text_height_get_clamped();
      iVar7 = device_info_text_width_get();
      iVar8 = device_info_text_height_get_clamped();
      gui_utf_draw(0,uVar6,0,iVar4 + 0xd2,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x52,1,0,0,0,0);
      uVar6 = get_localized_weekday_name(0x1f);
      iVar8 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar5 = iVar5 + 0x240;
      iVar7 = iVar7 + 0x88;
      iVar4 = iVar4 + 0x6d;
      iVar8 = iVar8 + 0x8a;
    }
control_label_00040b66:
    uVar13 = 1;
    goto control_label_00040a7e;
  default:
    goto switchD_000408e4_caseD_a;
  case 0xe:
  case 0xf:
    uVar6 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x36,uVar6,iVar4 + 0x37,0,0,0);
    iVar4 = get_device_info();
    if ((*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x0f') && (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) == '\x01'))
    goto switchD_000408e4_caseD_a;
    uVar6 = get_localized_weekday_name(0x23);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0xb8;
    break;
  case 0x10:
  case 0x11:
    iVar4 = get_device_info();
    if ((*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x11') && (B(((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/) == '\x01')) {
      uVar6 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      gui_bmp_bitmap_draw(0x38,uVar6,iVar4 + 0x37,0,0,0);
      goto switchD_000408e4_caseD_a;
    }
    iVar4 = device_info_text_width_get();
    iVar5 = device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x3c,iVar4 + 0x212,iVar5 + 4,0,0,0);
    iVar4 = device_info_text_width_get();
    iVar5 = device_info_text_height_get_clamped();
    iVar7 = device_info_text_width_get();
    iVar8 = device_info_text_height_get_clamped();
    gui_utf_draw(0,((unsigned long)&rodata_f341d) /*=0xf341d*/,3,iVar4 + 0x22e,iVar5 + 3,iVar7 + 0x23e,iVar8 + 0x1e,1,1,0,0,0);
    uVar6 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x38,uVar6,iVar4 + 4,0,0,0);
    uVar6 = get_localized_weekday_name(0x1a);
    iVar4 = device_info_text_width_get();
    iVar5 = device_info_text_height_get_clamped();
    iVar7 = device_info_text_width_get();
    iVar8 = device_info_text_height_get_clamped();
    gui_utf_draw(0,uVar6,0,iVar4 + 0x24,iVar5 + 3,iVar7 + 0x150,iVar8 + 0x1e,1,0,0,0,0);
    uVar6 = get_localized_weekday_name(0x1c);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x6d;
    uVar13 = 2;
control_label_00040bc6:
    iVar4 = iVar4 + 0x37;
control_label_000411c8:
    iVar5 = iVar5 + 0x240;
    goto control_label_00040a7e;
  case 0x16:
    uVar6 = get_localized_weekday_name(0x11);
    iVar8 = device_info_text_width_get();
    iVar4 = device_info_text_height_get_clamped();
    iVar5 = device_info_text_width_get();
    iVar7 = device_info_text_height_get_clamped();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x6a;
    break;
  case 0x17:
    iVar4 = get_ui_mode_flag_byte1();
    if (iVar4 == 6) {
      uVar6 = get_localized_weekday_name(0x12);
      iVar8 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar7 = iVar7 + 0x88;
      iVar5 = iVar5 + 0x240;
      iVar4 = iVar4 + 0x37;
      iVar8 = iVar8 + 0x48;
    }
    else {
      uVar6 = get_localized_weekday_name(0x12);
      iVar8 = device_info_text_width_get();
      iVar4 = device_info_text_height_get_clamped();
      iVar5 = device_info_text_width_get();
      iVar7 = device_info_text_height_get_clamped();
      iVar7 = iVar7 + 0x88;
      iVar5 = iVar5 + 0x240;
      iVar4 = iVar4 + 0x37;
      iVar8 = iVar8 + 0x88;
    }
  }
  uVar13 = 4;
control_label_00040a7e:
  gui_utf_draw(0,uVar6,0,iVar8,iVar4,iVar5,iVar7,uVar13,0,0,0,0);
switchD_000408e4_caseD_a:
  iVar4 = get_device_info();
  *(undefined1 *)(((unsigned long)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/ + 0x10) = *(undefined1 *)(iVar4 + 0xee4);
  return;
}
