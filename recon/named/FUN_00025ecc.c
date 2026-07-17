/* readable reconstruction; identity: FUN_00025ecc @ 0x00025ecc
 * public-name: FUN_00025ecc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 * address symbols (name @ address):
 *   g_level_calc_result_cache                @ 0x200023f4
 *   g_panel_calib_last_divisor               @ 0x200023f8
 *   g_level_calc_input_c_cache               @ 0x20003024
 *   g_panel_calib_last_param84               @ 0x20007a98
 *   g_level_calc_input_sl_cache              @ 0x20007a9c
 *   g_level_calc_input_b_cache               @ 0x20018c6b
 */
/* Reconstructed FUN_00025ecc @ 0x25ecc  (parity: 300/300 trials, PROVEN) */
extern void get_device_type(void);
int FUN_00025ecc(char *param_1){
  int iVar10 = *(int*)(param_1+0x84);
  int iVar8  = *(int*)(param_1+0x88);
  unsigned char bVar1 = (unsigned char)param_1[0x10];
  char cVar2 = param_1[0x11];
  int sl = *(int*)(param_1+0x80);
  if (sl != *(volatile int*)0x20007a9cUL
      || (unsigned)*(volatile unsigned char*)0x20018c6bUL != (unsigned)bVar1
      || *(volatile char*)0x20003024UL != cVar2
      || *(volatile int*)0x200023f8UL != iVar8
      || *(volatile int*)0x20007a98UL != iVar10){
    *(volatile int*)0x20007a9cUL = sl;
    *(volatile unsigned char*)0x20018c6bUL = bVar1;
    *(volatile char*)0x20003024UL = cVar2;
    *(volatile int*)0x200023f8UL = iVar8;
    *(volatile int*)0x20007a98UL = iVar10;
    int r6;
    if (cVar2 == 0) r6 = (int)0xfffffea2;
    else if (cVar2 == 2) r6 = 0x2bc;
    else r6 = 0;
    int iVar9 = (*param_1 == 2) ? 0x76c : 0xfa0;
    *(volatile int*)0x200023f4UL = (int)(iVar9 * (unsigned)bVar1) / iVar8;
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
  return *(volatile int*)0x200023f4UL;
}
