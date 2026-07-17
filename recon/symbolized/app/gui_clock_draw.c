#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000442bc @ 0x000442bc
 * public-name: gui_clock_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 * address symbols (name @ address):
 *   rodata_aaaac                             @ 0x000aaaac
 *   rodata_aaab7                             @ 0x000aaab7
 *   rodata_aaad4                             @ 0x000aaad4
 *   rodata_aad0b                             @ 0x000aad0b
 *   rodata_f02a3                             @ 0x000f02a3
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_000442bc @ 0x442bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef uint16_t undefined2; typedef unsigned int uint; typedef unsigned short ushort;
extern int log_message(int,...);
extern int strlen(int,...);
extern int get_device_info(int,...);
extern int debug_print(int,...);
extern int atomic_get_3_0(int,...);
extern int gui_utf_draw(int,...);
extern int resource_manger_get(int,...);
extern int clean_fb_data(int,...);
extern int reflash_fb_data_to_lcd(int,...);
extern int unix_timestamp_to_datetime(int,...);
extern int fb_blit_rows_copy(int,...);
extern int vdprintf_to_fd(int,...);

undefined4 gui_clock_draw(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,char param_7)
{
  int *piVar1; int *piVar2; int iVar3; uint32_t iVar4; int iVar5; uint uVar6;
  short sVar7; undefined4 uVar8; byte *pbVar9; int iVar10;
  int local_50; int local_4c; undefined4 local_48;
  struct {
    undefined4 word_0;
    undefined2 half_4;
    ushort hour_6;
    uint minute_8;
    byte text_12[20];
  } display;

  display.word_0 = 0; display.half_4 = 0; display.hour_6 = 0; display.minute_8 = 0;
  unix_timestamp_to_datetime(param_1,(int)&display.word_0);
  for (iVar10=0;iVar10<16;iVar10++) display.text_12[iVar10]=0;
  uVar6 = (uint)display.hour_6;
  if (param_7 == '\0') {
    if (uVar6 < 0xd) { if (uVar6 == 0) { display.hour_6 = 0xc; } }
    else { display.hour_6 = display.hour_6 - 0xc; }
    uVar6 = display.hour_6 / 10;
    sVar7 = display.hour_6 + (short)uVar6 * -10;
  } else {
    uVar6 = uVar6 / 10;
    sVar7 = display.hour_6 + (short)uVar6 * -10;
  }
  vdprintf_to_fd((int)display.text_12,0,0x10,((unsigned long)&rodata_aaaac) /*=0xaaaac*/,uVar6,sVar7,((unsigned long)&rodata_f02a3) /*=0xf02a3*/,
               (display.minute_8 & 0xffff) / 10,
               (display.minute_8 & 0xffff) % 10);
  iVar3 = strlen((int)display.text_12);
  switch(param_6) {
  case 0:
    uVar8 = 0;
    break;
  case 1:
    iVar4 = atomic_get_3_0(0);
    if ((iVar4 & 2u) != 0) {
      clean_fb_data(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,0,param_2,param_3,param_4,param_5);
    }
    piVar2 = (int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/; piVar1 = (int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    pbVar9 = display.text_12; iVar4 = param_2;
    for (iVar10 = 0; iVar3 != iVar10; iVar10 = iVar10 + 1) {
      local_50 = 0;
      iVar5 = resource_manger_get(1,*pbVar9,(int)&local_4c,(int)&local_48,(int)&local_50,0);
      if ((iVar5 == 0) && (local_50 != 0)) {
        fb_blit_rows_copy(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,local_50,local_4c / 2,local_48,iVar4,param_3);
        iVar4 = iVar4 + local_4c + 6;
      } else if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
          log_message(((unsigned long)&rodata_aaad4) /*=0xaaad4*/,((unsigned long)&rodata_aad0b) /*=0xaad0b*/,(uint)*pbVar9,((unsigned long)&rodata_aaab7) /*=0xaaab7*/);
        } else { debug_print(((unsigned long)&rodata_aaad4) /*=0xaaad4*/,((unsigned long)&rodata_aad0b) /*=0xaad0b*/,(uint)*pbVar9,((unsigned long)&rodata_aaab7) /*=0xaaab7*/); }
      }
      pbVar9 = pbVar9 + 1;
    }
    goto LAB_000443e4;
  case 2:
    iVar4 = atomic_get_3_0(0);
    if ((iVar4 & 2u) != 0) {
      clean_fb_data(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,0,param_2,param_3,param_4,param_5);
    }
    piVar2 = (int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/; piVar1 = (int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    iVar10 = 0; pbVar9 = display.text_12; iVar4 = param_2;
    while (iVar3 != iVar10) {
      local_50 = 0;
      iVar5 = resource_manger_get(2,*pbVar9,(int)&local_4c,(int)&local_48,(int)&local_50,0);
      iVar10 = iVar10 + 1;
      if ((iVar5 == 0) && (local_50 != 0)) {
        fb_blit_rows_copy(*(volatile int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/,local_50,local_4c / 2,local_48,iVar4,param_3);
        if (pbVar9[1] == 0x3a) { iVar5 = local_4c + 7; } else { iVar5 = local_4c + 2; }
        iVar4 = iVar4 + iVar5;
        if (*pbVar9 == 0x3a) { iVar4 = iVar4 + 7; }
      } else if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
          log_message(((unsigned long)&rodata_aaad4) /*=0xaaad4*/,((unsigned long)&rodata_aad0b) /*=0xaad0b*/,(uint)*pbVar9,((unsigned long)&rodata_aaab7) /*=0xaaab7*/);
        } else { debug_print(((unsigned long)&rodata_aaad4) /*=0xaaad4*/,((unsigned long)&rodata_aad0b) /*=0xaad0b*/,(uint)*pbVar9,((unsigned long)&rodata_aaab7) /*=0xaaab7*/); }
      }
      pbVar9 = pbVar9 + 1;
    }
LAB_000443e4:
    iVar3 = atomic_get_3_0(0);
    if ((((uint32_t)iVar3) & 2u) == 0) { return 0; }
    iVar3 = get_device_info(0);
    uVar8 = *(undefined4 *)(iVar3 + 0xeb4);
    iVar3 = get_device_info(0);
    reflash_fb_data_to_lcd(uVar8,*(undefined4 *)(iVar3 + 0xeb8),param_2,param_3,param_4,param_5);
    return 0;
  case 3:
    uVar8 = 3;
    break;
  default:
    goto caseD_4;
  }
  gui_utf_draw(0,(int)display.text_12,uVar8,param_2,param_3,param_4,param_5,1,0,0,0,0);
caseD_4:
  (void)piVar1; (void)piVar2;
  return 0;
}
