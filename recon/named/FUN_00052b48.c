/* readable reconstruction; identity: FUN_00052b48 @ 0x00052b48
 * public-name: FUN_00052b48
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_service_register                 <= FUN_0005ad38 @ 0x0005ad38
 * address symbols (name @ address):
 *   g_200028b8                               @ 0x200028b8
 */
/* Reconstructed FUN_00052b48 @ 0x52b48  (parity: 300/300 trials, PROVEN) */

extern unsigned int bt_gatt_service_register(void *service);

unsigned int FUN_00052b48(void)
{
    return bt_gatt_service_register((void *)0x200028b8);
}
