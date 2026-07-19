/* readable reconstruction; identity: FUN_00019b2c @ 0x00019b2c
 * public-name: get_ancs_conn_handle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ancs_conn_handle                     <= FUN_00019b2c @ 0x00019b2c
 * address symbols (name @ address):
 *   g_ancs_conn                              @ 0x20007518
 */
/* Reconstructed FUN_00019b2c @ 0x19b2c  (parity: 300/300 trials, PROVEN) */

unsigned int get_ancs_conn_handle(void) {
    return *(volatile unsigned int*)0x20007518UL;
}
