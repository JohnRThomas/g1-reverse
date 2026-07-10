#include "g1_app_symbols.h"
/* named: cal_panel_canvas_coord */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed cal_panel_canvas_coord @ 0x42fb0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void debug_print(unsigned,unsigned,unsigned,int);
void cal_panel_canvas_coord(int *param_1, int *param_2)
{
  int iVar1, iVar3; char *pcVar2;
  if (param_1 != 0) {
    iVar3 = *param_1;
    iVar1 = get_device_info();
    switch (*(unsigned char*)(iVar1+0xec1)) {
      case 1: iVar1 = 0x16; break;
      case 2: iVar1 = 8; break;
      default: iVar1 = 0; break;
      case 4: iVar1 = -4; break;
      case 5: iVar1 = -8; break;
      case 6: iVar1 = -10; break;
      case 7: iVar1 = -0xc; break;
      case 8: iVar1 = -0xe; break;
      case 9: iVar1 = -0x10; break;
    }
    *(volatile int*)param_1 = iVar1;
    pcVar2 = (char*)get_device_info();
    if (*pcVar2 == 1) *(volatile int*)param_1 = -*(volatile int*)param_1;
    if ((*param_1 != iVar3) && (1 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/)) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        iVar1 = get_device_info();
        DEBUG_PRINT("%s(): canvas_distance_gear:%d, pos_x:%d\n" /*=0xaa7a2*/, "cal_panel_canvas_coord" /*=0xaa855*/, (unsigned)*(unsigned char*)(iVar1+0xec1), *param_1);
      } else {
        iVar1 = get_device_info();
        debug_print("%s(): canvas_distance_gear:%d, pos_x:%d\n" /*=0xaa7a2*/, "cal_panel_canvas_coord" /*=0xaa855*/, (unsigned)*(unsigned char*)(iVar1+0xec1), *param_1);
      }
    }
  }
  if (param_2 != 0) {
    iVar3 = *param_2;
    iVar1 = get_device_info();
    iVar1 = (8 - (unsigned)*(unsigned char*)(iVar1+0xec0)) * 0x23;
    *(volatile int*)param_2 = iVar1;
    if ((iVar1 - iVar3 != 0) && (1 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/)) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        iVar1 = get_device_info();
        DEBUG_PRINT("%s(): raster_height_gear:%d, pos_y:%d\n" /*=0xaa7cb*/, "cal_panel_canvas_coord" /*=0xaa855*/, (unsigned)*(unsigned char*)(iVar1+0xec0), *param_2);
        return;
      }
      iVar1 = get_device_info();
      debug_print("%s(): raster_height_gear:%d, pos_y:%d\n" /*=0xaa7cb*/, "cal_panel_canvas_coord" /*=0xaa855*/, (unsigned)*(unsigned char*)(iVar1+0xec0), *param_2);
      return;
    }
  }
  return;
}

