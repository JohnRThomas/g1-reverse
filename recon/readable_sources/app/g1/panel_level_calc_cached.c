#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_imu_fusion_state__param_0019           [param_0019; G1-original]
 * Raw function identity: 0x00025ecc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00025ecc @ 0x00025ecc
 * public-name: panel_level_calc_cached
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 *   panel_level_calc_cached                  <= FUN_00025ecc @ 0x00025ecc
 * address symbols (name @ address):
 *   g_level_calc_result_cache                @ 0x200023f4
 *   g_panel_calib_last_divisor               @ 0x200023f8
 *   g_level_calc_input_c_cache               @ 0x20003024
 *   g_panel_calib_last_param84               @ 0x20007a98
 *   g_level_calc_input_sl_cache              @ 0x20007a9c
 *   g_level_calc_input_b_cache               @ 0x20018c6b
 */
/* Reconstructed FUN_00025ecc @ 0x25ecc  (parity: 300/300 trials, PROVEN) */
extern int get_device_type(void);
int panel_level_calc_cached(char *param_1){
  int iVar10 = *(int*)(param_1+0x84);
  int iVar8  = *(int*)(param_1+0x88);
  unsigned char bVar1 = (unsigned char)param_1[0x10];
  char cVar2 = param_1[0x11];
  int sl = *(int*)(param_1+0x80);
  if (sl != *(volatile int*)((unsigned long)&g_level_calc_input_sl_cache) /*=0x20007a9c*/
      || (unsigned)*(volatile unsigned char*)((unsigned long)&g_level_calc_input_b_cache) /*=0x20018c6b*/ != (unsigned)bVar1
      || *(volatile char*)((unsigned long)&g_level_calc_input_c_cache) /*=0x20003024*/ != cVar2
      || *(volatile int*)((unsigned long)&g_panel_calib_last_divisor) /*=0x200023f8*/ != iVar8
      || *(volatile int*)((unsigned long)&g_panel_calib_last_param84) /*=0x20007a98*/ != iVar10){
    *(volatile int*)((unsigned long)&g_level_calc_input_sl_cache) /*=0x20007a9c*/ = sl;
    *(volatile unsigned char*)((unsigned long)&g_level_calc_input_b_cache) /*=0x20018c6b*/ = bVar1;
    *(volatile char*)((unsigned long)&g_level_calc_input_c_cache) /*=0x20003024*/ = cVar2;
    *(volatile int*)((unsigned long)&g_panel_calib_last_divisor) /*=0x200023f8*/ = iVar8;
    *(volatile int*)((unsigned long)&g_panel_calib_last_param84) /*=0x20007a98*/ = iVar10;
    int r6;
    if (cVar2 == 0) r6 = (int)0xfffffea2;
    else if (cVar2 == 2) r6 = 0x2bc;
    else r6 = 0;
    int iVar9 = (*param_1 == 2) ? 0x76c : 0xfa0;
    *(volatile int*)((unsigned long)&g_level_calc_result_cache) /*=0x200023f4*/ = (int)(iVar9 * (unsigned)bVar1) / iVar8;
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
  return *(volatile int*)((unsigned long)&g_level_calc_result_cache) /*=0x200023f4*/;
}
