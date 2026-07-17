/* readable reconstruction; identity: FUN_0007f4cc @ 0x0007f4cc
 * public-name: bt_gatt_dm_attr_cnt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_dm_attr_cnt                      <= FUN_0007f4cc @ 0x0007f4cc
 */
/* Reconstructed FUN_0007f4cc @ 0x7f4cc  (parity: 300/300 trials, PROVEN) */

unsigned int bt_gatt_dm_attr_cnt(char *param_1)
{
    return *(volatile unsigned int *)(param_1 + 0x134);
}
