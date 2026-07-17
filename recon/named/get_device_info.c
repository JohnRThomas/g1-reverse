/* readable reconstruction; identity: FUN_000167a8 @ 0x000167a8
 * public-name: get_device_info
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 */
/* Reconstructed get_device_info @ 0x167a8  (parity: 300/300 trials, PROVEN) */

unsigned int get_device_info(void){
    return *(unsigned int*)0x200069fcUL;
}
