/* readable reconstruction; identity: FUN_000181f0 @ 0x000181f0
 * public-name: ancs_notify_sync_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_notify_sync_init                    <= FUN_000181f0 @ 0x000181f0
 *   ancs_gatt_client_cb_set                  <= FUN_0004f500 @ 0x0004f500
 * address symbols (name @ address):
 *   g_ancs_notify_sync_obj                   @ 0x20002310
 */
/* Reconstructed FUN_000181f0 @ 0x181f0  (parity: 300/300 trials, PROVEN) */

extern int ancs_gatt_client_cb_set(const unsigned long*);
int ancs_notify_sync_init(void) {
    return ancs_gatt_client_cb_set((void*)0x20002310UL);
}
