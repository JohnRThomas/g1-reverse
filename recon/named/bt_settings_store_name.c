/* readable reconstruction; identity: FUN_00053098 @ 0x00053098
 * public-name: bt_settings_store_name
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 *   bt_settings_store_name                   <= FUN_00053098 @ 0x00053098
 * address symbols (name @ address):
 *   rodata_f33e4                             @ 0x000f33e4
 */
/* Reconstructed FUN_00053098 @ 0x53098  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void bt_settings_store_name(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    bt_settings_store(0xf33e4UL, 0, 0, param_1, param_2, param_2, param_3);
}
