/* readable reconstruction; identity: FUN_0003cb4c @ 0x0003cb4c
 * public-name: update_not_disturb_settings
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_not_disturb_settings                   @ 0x2001b9aa
 */
/* Reconstructed update_not_disturb_settings @ 0x3cb4c  (parity: 300/300 trials, PROVEN) */

void update_not_disturb_settings(void){
    *(volatile unsigned char*)0x2001b9aaUL = 0;
}
