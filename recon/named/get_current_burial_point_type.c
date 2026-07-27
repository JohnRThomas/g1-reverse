/* readable reconstruction; identity: FUN_0007dac0 @ 0x0007dac0
 * public-name: get_current_burial_point_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   update_burial_point_day_index            <= FUN_0004a5b0 @ 0x0004a5b0
 *   get_current_burial_point_type            <= FUN_0007dac0 @ 0x0007dac0
 */
/* Reconstructed FUN_0007dac0 @ 0x7dac0  (parity: 300/300 trials, PROVEN) */

extern int update_burial_point_day_index(void);
extern int get_device_info(void);
unsigned int get_current_burial_point_type(void) {
  unsigned char uVar1;
  int iVar2;
  iVar2 = update_burial_point_day_index();
  if (iVar2 == 0) {
    iVar2 = get_device_info();
    uVar1 = *(volatile unsigned char *)(iVar2 + 0x10db);
  } else {
    uVar1 = 7;
  }
  return uVar1;
}
