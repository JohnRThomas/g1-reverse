/* named: gui_clock_draw */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_clock_draw @ 0x442bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef uint16_t undefined2; typedef unsigned int uint; typedef unsigned short ushort;
extern int DEBUG_PRINT(int,...);
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
  int *piVar1; int *piVar2; int iVar3; int iVar4; int iVar5; uint uVar6;
  short sVar7; undefined4 uVar8; byte *pbVar9; int iVar10;
  int local_50; int local_4c; undefined4 local_48; undefined4 local_44;
  undefined2 uStack_40; ushort local_3e; uint local_3c; byte local_38[20];

  local_44 = 0; uStack_40 = 0; local_3e = 0; local_3c = 0;
  unix_timestamp_to_datetime(param_1,(int)&local_44);
  for (iVar10=0;iVar10<16;iVar10++) local_38[iVar10]=0;
  uVar6 = (uint)local_3e;
  if (param_7 == '\0') {
    if (uVar6 < 0xd) { if (uVar6 == 0) { local_3e = 0xc; } }
    else { local_3e = local_3e - 0xc; }
    uVar6 = local_3e / 10;
    sVar7 = local_3e + (short)uVar6 * -10;
  } else {
    uVar6 = uVar6 / 10;
    sVar7 = local_3e + (short)uVar6 * -10;
  }
  vdprintf_to_fd((int)local_38,0,0x10,0xaaaac,uVar6,sVar7,0xf02a3,(local_3c & 0xffff) / 10,
               (local_3c & 0xffff) % 10);
  iVar3 = strlen((int)local_38);
  switch(param_6) {
  case 0:
    uVar8 = 0;
    break;
  case 1:
    iVar4 = atomic_get_3_0(0);
    if (iVar4 << 0x1e < 0) {
      clean_fb_data(*(volatile int*)0x2000a034,0,param_2,param_3,param_4,param_5);
    }
    piVar2 = (int*)0x20007554; piVar1 = (int*)0x2000230c;
    pbVar9 = local_38; iVar4 = param_2;
    for (iVar10 = 0; iVar3 != iVar10; iVar10 = iVar10 + 1) {
      local_50 = 0;
      iVar5 = resource_manger_get(1,*pbVar9,(int)&local_4c,(int)&local_48,(int)&local_50,0);
      if ((iVar5 == 0) && (local_50 != 0)) {
        fb_blit_rows_copy(*(volatile int*)0x2000a034,local_50,local_4c / 2,local_48,iVar4,param_3);
        iVar4 = iVar4 + local_4c + 6;
      } else if (1 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) {
          DEBUG_PRINT(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7);
        } else { debug_print(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7); }
      }
      pbVar9 = pbVar9 + 1;
    }
    goto LAB_000443e4;
  case 2:
    iVar4 = atomic_get_3_0(0);
    if (iVar4 << 0x1e < 0) {
      clean_fb_data(*(volatile int*)0x2000a034,0,param_2,param_3,param_4,param_5);
    }
    piVar2 = (int*)0x20007554; piVar1 = (int*)0x2000230c;
    iVar10 = 0; pbVar9 = local_38; iVar4 = param_2;
    while (iVar3 != iVar10) {
      local_50 = 0;
      iVar5 = resource_manger_get(2,*pbVar9,(int)&local_4c,(int)&local_48,(int)&local_50,0);
      iVar10 = iVar10 + 1;
      if ((iVar5 == 0) && (local_50 != 0)) {
        fb_blit_rows_copy(*(volatile int*)0x2000a034,local_50,local_4c / 2,local_48,iVar4,param_3);
        if (pbVar9[1] == 0x3a) { iVar5 = local_4c + 7; } else { iVar5 = local_4c + 2; }
        iVar4 = iVar4 + iVar5;
        if (*pbVar9 == 0x3a) { iVar4 = iVar4 + 7; }
      } else if (1 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) {
          DEBUG_PRINT(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7);
        } else { debug_print(0xaaad4,0xaad0b,(uint)*pbVar9,0xaaab7); }
      }
      pbVar9 = pbVar9 + 1;
    }
LAB_000443e4:
    iVar3 = atomic_get_3_0(0);
    if (-1 < iVar3 << 0x1e) { return 0; }
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
  gui_utf_draw(0,(int)local_38,uVar8,param_2,param_3,param_4,param_5,1,0,0,0,0);
caseD_4:
  (void)piVar1; (void)piVar2;
  return 0;
}

