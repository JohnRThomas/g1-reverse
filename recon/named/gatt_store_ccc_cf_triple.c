/* readable reconstruction; identity: FUN_00082fa6 @ 0x00082fa6
 * public-name: gatt_store_ccc_cf_triple
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_store_ccc_cf                        <= FUN_00082f3a @ 0x00082f3a
 *   gatt_store_ccc_cf_triple                 <= FUN_00082fa6 @ 0x00082fa6
 */
/* Reconstructed FUN_00082fa6 @ 0x82fa6  (parity: 300/300 trials, PROVEN) */

extern void gatt_store_ccc_cf(unsigned char, int);

void gatt_store_ccc_cf_triple(int param_1)
{
    gatt_store_ccc_cf(*(unsigned char*)(param_1 - 0x28), param_1 - 0x27);
    gatt_store_ccc_cf(*(unsigned char*)(param_1 - 0x1c), param_1 - 0x1b);
    gatt_store_ccc_cf(*(unsigned char*)(param_1 - 0x10), param_1 - 0xf);
    return;
}
