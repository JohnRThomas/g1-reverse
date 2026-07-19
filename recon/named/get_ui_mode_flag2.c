/* readable reconstruction; identity: FUN_00023eec @ 0x00023eec
 * public-name: get_ui_mode_flag2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag2                        <= FUN_00023eec @ 0x00023eec
 * address symbols (name @ address):
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed FUN_00023eec @ 0x23eec  (parity: 300/300 trials, PROVEN) */

unsigned char get_ui_mode_flag2(void) {
    return *(volatile unsigned char*)(0x20018462UL + 2);
}
