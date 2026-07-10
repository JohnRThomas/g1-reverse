#include "g1_app_symbols.h"
/* named: FUN_00025ecc */
/* Reconstructed FUN_00025ecc @ 0x25ecc  (parity: 300/300 trials, PROVEN) */
extern void get_device_type(void);
int FUN_00025ecc(char *param_1){
  int iVar10 = *(int*)(param_1+0x84);
  int iVar8  = *(int*)(param_1+0x88);
  unsigned char bVar1 = (unsigned char)param_1[0x10];
  char cVar2 = param_1[0x11];
  int sl = *(int*)(param_1+0x80);
  if (sl != *(volatile int*)((uintptr_t)&g_level_calc_input_sl_cache) /*=0x20007a9c*/
      || (unsigned)*(volatile unsigned char*)((uintptr_t)&g_level_calc_input_b_cache) /*=0x20018c6b*/ != (unsigned)bVar1
      || *(volatile char*)((uintptr_t)&g_level_calc_input_c_cache) /*=0x20003024*/ != cVar2
      || *(volatile int*)((uintptr_t)&g_panel_calib_last_divisor) /*=0x200023f8*/ != iVar8
      || *(volatile int*)((uintptr_t)&g_panel_calib_last_param84) /*=0x20007a98*/ != iVar10){
    *(volatile int*)((uintptr_t)&g_level_calc_input_sl_cache) /*=0x20007a9c*/ = sl;
    *(volatile unsigned char*)((uintptr_t)&g_level_calc_input_b_cache) /*=0x20018c6b*/ = bVar1;
    *(volatile char*)((uintptr_t)&g_level_calc_input_c_cache) /*=0x20003024*/ = cVar2;
    *(volatile int*)((uintptr_t)&g_panel_calib_last_divisor) /*=0x200023f8*/ = iVar8;
    *(volatile int*)((uintptr_t)&g_panel_calib_last_param84) /*=0x20007a98*/ = iVar10;
    int r6;
    if (cVar2 == 0) r6 = (int)0xfffffea2;
    else if (cVar2 == 2) r6 = 0x2bc;
    else r6 = 0;
    int iVar9 = (*param_1 == 2) ? 0x76c : 0xfa0;
    *(volatile int*)((uintptr_t)&g_level_calc_result_cache) /*=0x200023f4*/ = (int)(iVar9 * (unsigned)bVar1) / iVar8;
    get_device_type();
    int iv8b = *(int*)(param_1+0x84);
    int acc = 0x32 * (int)(short)(unsigned short)bVar1 + r6;
    if (iv8b == 0 && *(int*)(param_1+0x80) == 0){
      *(int*)(param_1+8) = acc - 0x189c;
      *(int*)(param_1+0xc) = acc - 0x2454;
    } else {
      *(int*)(param_1+8) = iv8b - acc;
      *(int*)(param_1+0xc) = (iv8b - 0x1194) - acc;
    }
  }
  return *(volatile int*)((uintptr_t)&g_level_calc_result_cache) /*=0x200023f4*/;
}

