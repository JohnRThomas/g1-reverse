/* readable reconstruction; identity: FUN_00053008 @ 0x00053008
 * public-name: sc_store_to_settings
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 *   sc_store_to_settings                     <= FUN_00053008 @ 0x00053008
 * address symbols (name @ address):
 *   rodata_f4de3                             @ 0x000f4de3
 */
/* Reconstructed FUN_00053008 @ 0x53008  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);

void sc_store_to_settings(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    bt_settings_store(0xf4de3U, param_1, param_2, param_3, param_4, param_2, param_3);
}
