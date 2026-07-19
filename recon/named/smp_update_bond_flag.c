/* readable reconstruction; identity: FUN_0005e5b8 @ 0x0005e5b8
 * public-name: smp_update_bond_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_pub_key_gen                           <= FUN_00055d08 @ 0x00055d08
 *   smp_update_bond_flag                     <= FUN_0005e5b8 @ 0x0005e5b8
 * address symbols (name @ address):
 *   g_ble_dev_state                          @ 0x20002000
 *   g_bt_smp_settings_load_cb                @ 0x20002a50
 *   g_bt_settings_load_done                  @ 0x2001d532
 */
/* Reconstructed FUN_0005e5b8 @ 0x5e5b8  (parity: 300/300 trials, PROVEN) */

extern void bt_pub_key_gen(unsigned int);
unsigned int smp_update_bond_flag(void)
{
  unsigned int uVar1;
  uVar1 = 0x20002a50UL;
  *(volatile unsigned char*)0x2001d532UL = ((*(volatile unsigned char*)(0x20002000UL + 0xa2)) & 6) == 6;
  bt_pub_key_gen(uVar1);
  return 0;
}
