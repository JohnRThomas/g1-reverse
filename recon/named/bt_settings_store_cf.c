/* readable reconstruction; identity: FUN_00053034 @ 0x00053034
 * public-name: bt_settings_store_cf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 *   bt_settings_store_cf                     <= FUN_00053034 @ 0x00053034
 * address symbols (name @ address):
 *   rodata_f4ddd                             @ 0x000f4ddd
 */
/* Reconstructed FUN_00053034 @ 0x53034  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);

void bt_settings_store_cf(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    bt_settings_store(0xf4dddU, param_1, param_2, param_3, param_4, param_2, param_3);
}
