/* readable reconstruction; identity: FUN_00034410 @ 0x00034410
 * public-name: get_message_pending_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_message_pending_state                <= FUN_00034410 @ 0x00034410
 * address symbols (name @ address):
 *   g_message_pending_state                  @ 0x2001a229
 */
/* Reconstructed FUN_00034410 @ 0x34410  (parity: 300/300 trials, PROVEN) */

unsigned char get_message_pending_state(void) {
    return *(volatile unsigned char*)0x2001a229UL;
}
