/* readable reconstruction; identity: FUN_0005307c @ 0x0005307c
 * public-name: store_gatt_db_hash_setting
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 *   store_gatt_db_hash_setting               <= FUN_0005307c @ 0x0005307c
 * address symbols (name @ address):
 *   rodata_f4a01                             @ 0x000f4a01
 */
/* Reconstructed FUN_0005307c @ 0x5307c  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void store_gatt_db_hash_setting(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    bt_settings_store(0xf4a01UL, 0, 0, param_1, param_2, param_2, param_3);
}
