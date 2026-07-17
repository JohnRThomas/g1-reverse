/* readable reconstruction; identity: FUN_00019b2c @ 0x00019b2c
 * public-name: FUN_00019b2c
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ancs_conn                              @ 0x20007518
 */
/* Reconstructed FUN_00019b2c @ 0x19b2c  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00019b2c(void) {
    return *(volatile unsigned int*)0x20007518UL;
}
