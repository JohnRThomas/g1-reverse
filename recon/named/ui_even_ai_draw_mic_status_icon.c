/* named: ui_even_ai_draw_mic_status_icon */
/* Reconstructed ui_even_ai_draw_mic_status_icon @ 0x3cb58  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned long long undefined8;
extern int get_device_info(int,...); extern int gui_set_active_canvas(int,...); extern int gui_screen_clear(int,...);
extern int gui_canvas_flags_set_bit1(int,...); extern int gui_reset_dynamic_bitmap_frame_state(int,...); extern int gui_bmp_dynamic_bitmap_draw(int,...);
extern int gui_bmp_bitmap_draw(int,...); extern int gui_utf_draw(int,...);
extern unsigned long long k_uptime_get_5(int,...);
extern int device_info_text_width_get(int,...); extern int device_info_text_height_get_clamped(int,...); extern int get_localized_weekday_name(int,...);

undefined4 ui_even_ai_draw_mic_status_icon(int param_1,undefined4 param_2,int param_3)
{
  char cVar1; uint uVar2; uint uVar3; volatile char *pcVar4; int iVar5; int iVar6; undefined4 uVar7;
  int iVar8; int iVar9; uint uVar10; unsigned long long uVar11; int base;
  gui_set_active_canvas(param_1 + 0x24);
  pcVar4 = (volatile char*)0x2001b9aa;
  if (param_3 == 2) {
    gui_screen_clear(0);
    iVar5 = get_device_info(0);
    *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
    *pcVar4 = 0;
  }
  else if (*pcVar4 == 0) {
    gui_screen_clear(0); gui_canvas_flags_set_bit1(0); gui_reset_dynamic_bitmap_frame_state(0);
    *pcVar4 = 1;
    uVar11 = k_uptime_get_5(0);
    iVar5 = get_device_info(0);
    base = *(int*)(iVar5 + 0x1010);
    *(volatile uint*)(base + 7) = (uint)(uVar11 >> 32);
    *(volatile uint*)(base + 3) = (uint)uVar11;
    cVar1 = *(volatile char*)0x2001b9ab;
    if (cVar1 == 1) {
      iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
      gui_bmp_dynamic_bitmap_draw(7,iVar5 + 0xd8,iVar6 + 0x3a,0,0,0,1);
      uVar7 = get_localized_weekday_name(0x27);
      iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
      iVar8 = device_info_text_width_get(0); iVar9 = device_info_text_height_get_clamped(0);
      iVar5 = iVar5 + 0x10c;
    } else if (cVar1 == 2) {
      uVar7 = device_info_text_width_get(0); iVar5 = device_info_text_height_get_clamped(0);
      gui_bmp_bitmap_draw(0x48,uVar7,iVar5 + 0x3a,0,0,0);
      uVar7 = get_localized_weekday_name(0x26);
      iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
      iVar8 = device_info_text_width_get(0); iVar9 = device_info_text_height_get_clamped(0);
      iVar5 = iVar5 + 0x58;
    } else {
      if (cVar1 != 0) return 0;
      iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
      gui_bmp_dynamic_bitmap_draw(6,iVar5 + 0xec,iVar6 + 0x3a,0,0,0,1);
      uVar7 = get_localized_weekday_name(0x25);
      iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
      iVar8 = device_info_text_width_get(0); iVar9 = device_info_text_height_get_clamped(0);
      iVar5 = iVar5 + 0x120;
    }
    gui_utf_draw(0,uVar7,0,iVar5,iVar6 + 0x37,iVar8 + 0x240,iVar9 + 0x88,2,0,0,0,0);
  }
  else if (*pcVar4 == 1) {
    cVar1 = *(volatile char*)0x2001b9ab;
    if (cVar1 == 1) {
      iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
      gui_bmp_dynamic_bitmap_draw(7,iVar5 + 0xd8,iVar6 + 0x3a,0,0,0,1);
      uVar11 = k_uptime_get_5(0);
      iVar5 = get_device_info(0);
      base = *(int*)(iVar5 + 0x1010);
      uVar10 = *(uint*)(base + 3);
      uVar2 = (int)(uVar11 >> 32) - *(int*)(base + 7);
      uVar3 = (uint)((uint)uVar11 < uVar10);
      if (uVar2 != uVar3 || uVar2 - uVar3 < (uint)(0x5db < (uint)uVar11 - uVar10)) {
        iVar5 = get_device_info(0);
        *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
      }
    } else {
      if (cVar1 == 2) {
        uVar11 = k_uptime_get_5(0);
        iVar5 = get_device_info(0);
        base = *(int*)(iVar5 + 0x1010);
        uVar10 = *(uint*)(base + 3);
        uVar2 = (int)(uVar11 >> 32) - *(int*)(base + 7);
        uVar3 = (uint)((uint)uVar11 < uVar10);
        if (uVar2 == uVar3 && (uint)(0x5db < (uint)uVar11 - uVar10) <= uVar2 - uVar3) return 0;
      } else if (cVar1 == 0) {
        iVar5 = device_info_text_width_get(0); iVar6 = device_info_text_height_get_clamped(0);
        gui_bmp_dynamic_bitmap_draw(6,iVar5 + 0xec,iVar6 + 0x3a,0,0,0,1);
        uVar11 = k_uptime_get_5(0);
        iVar5 = get_device_info(0);
        base = *(int*)(iVar5 + 0x1010);
        uVar10 = *(uint*)(base + 3);
        uVar2 = (int)(uVar11 >> 32) - *(int*)(base + 7);
        uVar3 = (uint)((uint)uVar11 < uVar10);
        if (uVar2 == uVar3 && (uint)(0x5db < (uint)uVar11 - uVar10) <= uVar2 - uVar3) return 0;
        iVar5 = get_device_info(0);
        *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
        return 0;
      }
      iVar5 = get_device_info(0);
      *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
    }
  }
  return 0;
}

