/* readable reconstruction; identity: FUN_000269fc @ 0x000269fc
 * public-name: get_last_standby_event_id
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_last_standby_event_id                <= FUN_000269fc @ 0x000269fc
 * address symbols (name @ address):
 *   g_last_standby_event_id                  @ 0x2000302d
 */
/* Reconstructed FUN_000269fc @ 0x269fc  (parity: 300/300 trials, PROVEN) */

unsigned char get_last_standby_event_id(void) {
    return *(volatile unsigned char*)0x2000302dUL;
}
