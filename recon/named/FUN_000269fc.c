/* readable reconstruction; identity: FUN_000269fc @ 0x000269fc
 * public-name: FUN_000269fc
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_last_standby_event_id                  @ 0x2000302d
 */
/* Reconstructed FUN_000269fc @ 0x269fc  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_000269fc(void) {
    return *(volatile unsigned char*)0x2000302dUL;
}
