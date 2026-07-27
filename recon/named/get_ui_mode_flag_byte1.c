/* readable reconstruction; identity: FUN_00023ee0 @ 0x00023ee0
 * public-name: get_ui_mode_flag_byte1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 * address symbols (name @ address):
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed FUN_00023ee0 @ 0x23ee0  (parity: 300/300 trials, PROVEN) */

int get_ui_mode_flag_byte1(void) {
    return *(volatile unsigned char*)(0x20018462UL + 1);
}
