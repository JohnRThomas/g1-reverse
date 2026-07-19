/* readable reconstruction; identity: FUN_0007c1dc @ 0x0007c1dc
 * public-name: store_device_info_bytes_cd_cf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   device_info_set_bytes_cc_ce              <= FUN_0007c176 @ 0x0007c176
 *   store_device_info_bytes_cd_cf            <= FUN_0007c1dc @ 0x0007c1dc
 */
/* Reconstructed FUN_0007c1dc @ 0x7c1dc  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void device_info_set_bytes_cc_ce(void);
unsigned int store_device_info_bytes_cd_cf(unsigned char param_1, unsigned char param_2, int param_3)
{
  int iVar1;
  if (param_3 == 0) {
    iVar1 = get_device_info();
    *(volatile unsigned char *)(iVar1 + 0xcf) = param_2;
    iVar1 = get_device_info();
    *(volatile unsigned char *)(iVar1 + 0xcd) = param_1;
  } else {
    device_info_set_bytes_cc_ce();
  }
  return 0;
}
