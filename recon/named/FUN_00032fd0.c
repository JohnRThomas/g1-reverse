/* readable reconstruction; identity: FUN_00032fd0 @ 0x00032fd0
 * public-name: FUN_00032fd0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_click_dispatch_flag                    @ 0x20019ef2
 */
/* Reconstructed FUN_00032fd0 @ 0x32fd0  (parity: 300/300 trials, PROVEN) */

void FUN_00032fd0(unsigned char param_1) {
    *(volatile unsigned char*)0x20019ef2UL = param_1;
}
