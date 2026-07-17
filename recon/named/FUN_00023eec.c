/* readable reconstruction; identity: FUN_00023eec @ 0x00023eec
 * public-name: FUN_00023eec
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed FUN_00023eec @ 0x23eec  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00023eec(void) {
    return *(volatile unsigned char*)(0x20018462UL + 2);
}
