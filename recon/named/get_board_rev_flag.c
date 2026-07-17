/* readable reconstruction; identity: FUN_00025284 @ 0x00025284
 * public-name: get_board_rev_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_board_rev_flag                       <= FUN_00025284 @ 0x00025284
 * address symbols (name @ address):
 *   g_board_rev_flag                         @ 0x20018c69
 */
/* Reconstructed FUN_00025284 @ 0x25284  (parity: 300/300 trials, PROVEN) */

unsigned char get_board_rev_flag(void) {
    return *(volatile unsigned char*)0x20018c69UL;
}
