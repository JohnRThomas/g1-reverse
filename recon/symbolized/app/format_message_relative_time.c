#include "g1_app_symbols.h"
/* named: format_message_relative_time */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed format_message_relative_time @ 0x357dc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort; typedef unsigned char byte;
extern int DEBUG_PRINT(int,...); extern int get_device_info(int,...); extern int debug_print(int,...);
extern int FUN_00023ee0(int,...); extern int gui_utf_draw_align_right(int,...); extern int clean_fb_data(int,...);
extern int unix_timestamp_to_datetime(int,...); extern int debug_print_burial_point_date(int,...); extern int format_string_to_buffer(int,...);
extern int get_timestamp(int,...); extern int device_info_text_width_get(int,...); extern int device_info_text_height_get_clamped(int,...);
extern int memset_bytes(int,...); extern int strcpy(int,...);

void format_message_relative_time(undefined4 param_1,int param_2)
{
  ushort uVar1; int *piVar2; int iVar3; int iVar4; undefined4 uVar5; int iVar6; int iVar7;
  ushort uVar8; uint uVar9; uint uVar10;
  undefined4 local_2c; undefined4 local_28; uint local_24;
  iVar3 = get_device_info(0);
  iVar4 = get_timestamp(0);
  piVar2 = (int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
  uVar10 = iVar4 - param_2;
  memset_bytes(param_1,0,0x20);
  uVar9 = uVar10 & ~((int)uVar10 >> 0x1f);
  if (*(volatile int*)piVar2 == 0) DEBUG_PRINT("currentTime is %d,recvTime is %d,unReadTime is %d \n" /*=0xa8ac7*/,iVar4,param_2,uVar9);
  else debug_print("currentTime is %d,recvTime is %d,unReadTime is %d \n" /*=0xa8ac7*/,iVar4,param_2,uVar9);
  iVar4 = FUN_00023ee0(0);
  if (iVar4 == 6) {
    uVar5 = "Jetzt" /*=0xa8afb*/;
    if (uVar10 - 0x3c <= 0x7fffffc3u) {
      if (uVar9 - 0x3c < 0xdd4) { uVar9 = uVar9 / 0x3c; uVar5 = "Vor %d Min." /*=0xa8b01*/; }
      else {
        if (0x1c1f < uVar9 - 0xe10) {
          if (uVar9 - 0x2a30 <= ((uintptr_t)&rodata_1274f) /*=0x1274f*/) {
            local_2c = 0; local_28 = 0; local_24 = 0;
            unix_timestamp_to_datetime(param_2,(int)&local_2c);
            uVar9 = local_24 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/; uVar5 = "%02d:%02d" /*=0xa9c18*/; uVar8 = (ushort)(local_28 >> 16);
            goto LAB_920;
          }
          uVar5 = "Gestern" /*=0xa8b19*/;
          if (((uintptr_t)&rodata_1517f) /*=0x1517f*/ < uVar9 - ((uintptr_t)&rodata_15180) /*=0x15180*/) {
            if (((uintptr_t)&rodata_6977f) /*=0x6977f*/ < uVar9 - ((uintptr_t)&rodata_2a300) /*=0x2a300*/) {
              local_2c = 0; local_28 = 0; local_24 = 0;
              unix_timestamp_to_datetime(param_2,(int)&local_2c);
              uVar8 = (ushort)local_28; uVar1 = (ushort)(local_2c >> 16);
              goto LAB_96a;
            }
LAB_948:
            uVar5 = debug_print_burial_point_date(param_2);
          }
          goto LAB_82e;
        }
        uVar9 = uVar9 / 0xe10; uVar5 = "Vor %d Std." /*=0xa8b0d*/;
      }
LAB_858:
      format_string_to_buffer(param_1,uVar5,uVar9);
      goto LAB_85e;
    }
  } else {
    uVar5 = "Now" /*=0xa8b2b*/;
    if (uVar10 - 0x3c <= 0x7fffffc3u) {
      if (uVar9 - 0x3c < 0xdd4) { uVar9 = uVar9 / 0x3c; uVar5 = "%dm ago" /*=0xa8b2f*/; }
      else {
        if (0x1c1f < uVar9 - 0xe10) {
          if (((uintptr_t)&rodata_1274f) /*=0x1274f*/ < uVar9 - 0x2a30) {
            uVar5 = "Yesterday" /*=0xa8b96*/;
            if (uVar9 - ((uintptr_t)&rodata_15180) /*=0x15180*/ <= ((uintptr_t)&rodata_1517f) /*=0x1517f*/) goto LAB_82e;
            if (uVar9 - ((uintptr_t)&rodata_2a300) /*=0x2a300*/ <= ((uintptr_t)&rodata_6977f) /*=0x6977f*/) goto LAB_948;
            local_2c = 0; local_28 = 0; local_24 = 0;
            unix_timestamp_to_datetime(param_2,(int)&local_2c);
            uVar8 = (ushort)(local_2c >> 16); uVar1 = (ushort)local_28;
LAB_96a:
            uVar9 = (uint)uVar1; uVar5 = "%02d/%02d" /*=0xa8b21*/;
          } else {
            local_2c = 0; local_28 = 0; local_24 = 0;
            unix_timestamp_to_datetime(param_2,(int)&local_2c);
            if (*(volatile int*)piVar2 == 0)
              DEBUG_PRINT("date: %u: %04d/%02d/%02d-%02d:%02d:%02d" /*=0xa8b3f*/,param_2,local_2c & ((uintptr_t)&tbl_ffc8) /*=0xffff*/,local_2c >> 0x10,local_28 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/,local_28 >> 0x10,local_24 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/,local_24 >> 0x10);
            else debug_print("date: %u: %04d/%02d/%02d-%02d:%02d:%02d" /*=0xa8b3f*/,param_2,local_2c & ((uintptr_t)&tbl_ffc8) /*=0xffff*/,local_2c >> 0x10);
            if (*(volatile int*)piVar2 == 0) { iVar4 = get_device_info(0); DEBUG_PRINT("time_disp_mode is %d \n" /*=0xa8b67*/,(uint)*(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e)); }
            else { iVar4 = get_device_info(0); debug_print("time_disp_mode is %d \n" /*=0xa8b67*/,*(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e)); }
            iVar4 = get_device_info(0);
            uVar9 = local_24 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/; uVar5 = "%02d:%02d" /*=0xa9c18*/; uVar8 = (ushort)(local_28 >> 16);
            if (*(char *)(*(int *)(iVar4 + 0xfec) + 0x5e) != 0) {
              if ((ushort)(local_28 >> 16) < 0xd) {
                uVar5 = "%02d:%02dam" /*=0xa8b8a*/;
                if ((ushort)(local_28 >> 16) == 0) { local_28 = (0xc << 16) | (ushort)local_28; uVar8 = 0xc; }
              } else {
                uVar8 = (ushort)(local_28 >> 16) - 0xc;
                local_28 = (((ushort)(local_28 >> 16) - 0xc) << 16) | (ushort)local_28;
                uVar5 = "%02d:%02dpm" /*=0xa8b7e*/;
              }
            }
          }
LAB_920:
          format_string_to_buffer(param_1,uVar5,uVar8,uVar9);
          goto LAB_85e;
        }
        uVar9 = uVar9 / 0xe10; uVar5 = "%dh ago" /*=0xa8b37*/;
      }
      goto LAB_858;
    }
  }
LAB_82e:
  strcpy(param_1,uVar5);
LAB_85e:
  iVar4 = device_info_text_width_get(0); uVar5 = device_info_text_height_get_clamped(0); iVar6 = device_info_text_width_get(0); iVar7 = device_info_text_height_get_clamped(0);
  clean_fb_data(iVar3 + 0xb90,0,iVar4 + 0x196,uVar5,iVar6 + 0x200,iVar7 + 0x1b);
  iVar3 = device_info_text_width_get(0); uVar5 = device_info_text_height_get_clamped(0); iVar4 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
  gui_utf_draw_align_right(0,param_1,0,iVar3 + 0x196,uVar5,iVar4 + 0x200,iVar6 + 0x1b,1,0,0,0,0);
  if (*(volatile int*)piVar2 == 0) { uVar5 = device_info_text_width_get(0); DEBUG_PRINT("gui_getScreenoffset_x=%d,timeDiffBuf is %s \n" /*=0xa8ba0*/,uVar5,param_1); return; }
  uVar5 = device_info_text_width_get(0); debug_print("gui_getScreenoffset_x=%d,timeDiffBuf is %s \n" /*=0xa8ba0*/,uVar5,param_1);
  return;
}

