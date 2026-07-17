/* readable reconstruction; identity: FUN_00034410 @ 0x00034410
 * public-name: FUN_00034410
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_message_pending_state                  @ 0x2001a229
 */
/* Reconstructed FUN_00034410 @ 0x34410  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00034410(void) {
    return *(volatile unsigned char*)0x2001a229UL;
}
