/* readable reconstruction; identity: FUN_00053050 @ 0x00053050
 * public-name: FUN_00053050
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 * address symbols (name @ address):
 *   rodata_f4aa1                             @ 0x000f4aa1
 */
/* Reconstructed FUN_00053050 @ 0x53050  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00053050(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    bt_settings_store(0xf4aa1UL, param_1, param_2, param_3, param_4, param_2, param_3);
}
