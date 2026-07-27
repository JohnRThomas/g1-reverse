/* readable reconstruction; identity: FUN_000357dc @ 0x000357dc
 * public-name: format_message_relative_time
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   format_message_relative_time             <= FUN_000357dc @ 0x000357dc
 *   gui_utf_draw_align_right                 <= FUN_00044ec4 @ 0x00044ec4
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   debug_print_burial_point_date            <= FUN_0004a2a4 @ 0x0004a2a4
 *   format_string_to_buffer                  <= FUN_0007797c @ 0x0007797c
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_1274f                             @ 0x0001274f
 *   rodata_a8ac7                             @ 0x000a8ac7   [INLINED -- G6 literal batch]
 *   rodata_a8afb                             @ 0x000a8afb
 *   rodata_a8b01                             @ 0x000a8b01
 *   rodata_a8b0d                             @ 0x000a8b0d
 *   rodata_a8b19                             @ 0x000a8b19
 *   rodata_a8b21                             @ 0x000a8b21
 *   rodata_a8b2b                             @ 0x000a8b2b
 *   rodata_a8b2f                             @ 0x000a8b2f
 *   rodata_a8b37                             @ 0x000a8b37
 *   rodata_a8b3f                             @ 0x000a8b3f   [INLINED -- G6 literal batch]
 *   rodata_a8b67                             @ 0x000a8b67   [INLINED -- G6 literal batch]
 *   rodata_a8b7e                             @ 0x000a8b7e
 *   rodata_a8b8a                             @ 0x000a8b8a
 *   rodata_a8b96                             @ 0x000a8b96
 *   rodata_a8ba0                             @ 0x000a8ba0   [INLINED -- G6 literal batch]
 *   rodata_a9c18                             @ 0x000a9c18
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_000357dc @ 0x357dc (strict CFG parity). */
#include <stdint.h>
#include "../headers/g1_log.h"
typedef uint32_t undefined4;
typedef uint32_t uint;
typedef uint16_t ushort;
typedef uint8_t byte;

extern int get_device_info(void);
extern int get_ui_mode_flag_byte1(void);
extern void gui_utf_draw_align_right(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                        uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                        uint32_t, uint32_t);
extern void clean_fb_data(uintptr_t, uint32_t, uint32_t, uint32_t, uint32_t,
                        uint32_t);
extern void unix_timestamp_to_datetime(uint32_t timestamp, uint32_t *calendar_fields);
extern uintptr_t debug_print_burial_point_date(uint32_t timestamp);
extern void format_string_to_buffer(uint32_t output, uintptr_t format, ...);
extern uint32_t get_timestamp(void);
extern uint32_t device_info_text_width_get(void);
extern uint32_t device_info_text_height_get_clamped(void);
extern void memset_bytes(void*, int, int);
extern char *strcpy(char *, const char *);

void format_message_relative_time(undefined4 param_1,int param_2)
{
  ushort uVar1; int *piVar2; int iVar3; int iVar4; undefined4 uVar5; int iVar6; int iVar7;
  ushort uVar8; uint uVar9; uint uVar10;
  uint32_t calendar[3];
  iVar3 = get_device_info();
  iVar4 = get_timestamp();
  piVar2 = (int*)0x20007554;
  uVar10 = iVar4 - param_2;
  memset_bytes(param_1,0,0x20);
  uVar9 = uVar10 & ~((int)uVar10 >> 0x1f);
  if (*(volatile int*)piVar2 == 0) log_message(((unsigned long)"currentTime is %d,recvTime is %d,unReadTime is %d \n"),iVar4,param_2,uVar9);
  else debug_print(((unsigned long)"currentTime is %d,recvTime is %d,unReadTime is %d \n"),iVar4,param_2,uVar9);
  iVar4 = get_ui_mode_flag_byte1();
  if (iVar4 == 6) {
    uVar5 = 0xa8afb;
    if (uVar10 - 0x3c <= 0x7fffffc3u) {
      if (uVar9 - 0x3c < 0xdd4) { uVar9 = uVar9 / 0x3c; uVar5 = 0xa8b01; }
      else {
        if (0x1c1f < uVar9 - 0xe10) {
          if (uVar9 - 0x2a30 <= 0x1274fu) {
            calendar[0] = 0; calendar[1] = 0; calendar[2] = 0;
            unix_timestamp_to_datetime(param_2,calendar);
            uVar9 = calendar[2] & 0xffff; uVar5 = 0xa9c18; uVar8 = (ushort)(calendar[1] >> 16);
            goto LAB_920;
          }
          uVar5 = 0xa8b19;
          if (0x1517fu < uVar9 - 0x15180) {
            if (0x6977fu < uVar9 - 0x2a300) {
              calendar[0] = 0; calendar[1] = 0; calendar[2] = 0;
              unix_timestamp_to_datetime(param_2,calendar);
              uVar8 = (ushort)calendar[1]; uVar1 = (ushort)(calendar[0] >> 16);
              goto LAB_96a;
            }
LAB_948:
            uVar5 = debug_print_burial_point_date(param_2);
          }
          goto LAB_82e;
        }
        uVar9 = uVar9 / 0xe10; uVar5 = 0xa8b0d;
      }
LAB_858:
      format_string_to_buffer(param_1,uVar5,uVar9);
      goto LAB_85e;
    }
  } else {
    uVar5 = 0xa8b2b;
    if (uVar10 - 0x3c <= 0x7fffffc3u) {
      if (uVar9 - 0x3c < 0xdd4) { uVar9 = uVar9 / 0x3c; uVar5 = 0xa8b2f; }
      else {
        if (0x1c1f < uVar9 - 0xe10) {
          if (0x1274fu < uVar9 - 0x2a30) {
            uVar5 = 0xa8b96;
            if (uVar9 - 0x15180 <= 0x1517fu) goto LAB_82e;
            if (uVar9 - 0x2a300 <= 0x6977fu) goto LAB_948;
            calendar[0] = 0; calendar[1] = 0; calendar[2] = 0;
            unix_timestamp_to_datetime(param_2,calendar);
            uVar8 = (ushort)(calendar[0] >> 16); uVar1 = (ushort)calendar[1];
LAB_96a:
            uVar9 = (uint)uVar1; uVar5 = 0xa8b21;
          } else {
            calendar[0] = 0; calendar[1] = 0; calendar[2] = 0;
            unix_timestamp_to_datetime(param_2,calendar);
            if (*(volatile int*)piVar2 == 0)
              log_message(((unsigned long)"date: %u: %04d/%02d/%02d-%02d:%02d:%02d"),param_2,calendar[0] & 0xffff,calendar[0] >> 0x10,calendar[1] & 0xffff,calendar[1] >> 0x10,calendar[2] & 0xffff,calendar[2] >> 0x10);
            else debug_print(((unsigned long)"date: %u: %04d/%02d/%02d-%02d:%02d:%02d"),param_2,calendar[0] & 0xffff,calendar[0] >> 0x10,calendar[1] & 0xffff,calendar[1] >> 0x10,calendar[2] & 0xffff,calendar[2] >> 0x10);
            if (*(volatile int*)piVar2 == 0) { iVar4 = get_device_info(); log_message(((unsigned long)"time_disp_mode is %d \n"),(uint)*(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e)); }
            else { iVar4 = get_device_info(); debug_print(((unsigned long)"time_disp_mode is %d \n"),*(byte *)(*(int *)(iVar4 + 0xfec) + 0x5e)); }
            iVar4 = get_device_info();
            uVar9 = calendar[2] & 0xffff; uVar5 = 0xa9c18; uVar8 = (ushort)(calendar[1] >> 16);
            if (*(char *)(*(int *)(iVar4 + 0xfec) + 0x5e) != 0) {
              if ((ushort)(calendar[1] >> 16) < 0xd) {
                uVar5 = 0xa8b8a;
                if ((ushort)(calendar[1] >> 16) == 0) { calendar[1] = (0xc << 16) | (ushort)calendar[1]; uVar8 = 0xc; }
              } else {
                uVar8 = (ushort)(calendar[1] >> 16) - 0xc;
                calendar[1] = (((ushort)(calendar[1] >> 16) - 0xc) << 16) | (ushort)calendar[1];
                uVar5 = 0xa8b7e;
              }
            }
          }
LAB_920:
          format_string_to_buffer(param_1,uVar5,uVar8,uVar9);
          goto LAB_85e;
        }
        uVar9 = uVar9 / 0xe10; uVar5 = 0xa8b37;
      }
      goto LAB_858;
    }
  }
LAB_82e:
  strcpy(param_1,uVar5);
LAB_85e:
  iVar4 = device_info_text_width_get(); uVar5 = device_info_text_height_get_clamped(); iVar6 = device_info_text_width_get(); iVar7 = device_info_text_height_get_clamped();
  clean_fb_data(iVar3 + 0xb90,0,iVar4 + 0x196,uVar5,iVar6 + 0x200,iVar7 + 0x1b);
  iVar3 = device_info_text_width_get(); uVar5 = device_info_text_height_get_clamped(); iVar4 = device_info_text_width_get(); iVar6 = device_info_text_height_get_clamped();
  gui_utf_draw_align_right(0,param_1,0,iVar3 + 0x196,uVar5,iVar4 + 0x200,iVar6 + 0x1b,1,0,0,0,0);
  if (*(volatile int*)piVar2 == 0) { uVar5 = device_info_text_width_get(); log_message(((unsigned long)"gui_getScreenoffset_x=%d,timeDiffBuf is %s \n"),uVar5,param_1); return; }
  uVar5 = device_info_text_width_get(); debug_print(((unsigned long)"gui_getScreenoffset_x=%d,timeDiffBuf is %s \n"),uVar5,param_1);
  return;
}
