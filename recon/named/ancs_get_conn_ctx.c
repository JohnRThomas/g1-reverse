/* readable reconstruction; identity: FUN_000181fc @ 0x000181fc
 * public-name: ancs_get_conn_ctx
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 * address symbols (name @ address):
 *   g_ble_conn_ctx_ptr                       @ 0x20006a30
 */
/* Reconstructed FUN_000181fc @ 0x181fc  (parity: 300/300 trials, PROVEN) */

int ancs_get_conn_ctx(void) {
    return *(volatile unsigned int *)0x20006a30UL;
}
