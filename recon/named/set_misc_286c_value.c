/* readable reconstruction; identity: FUN_00051038 @ 0x00051038
 * public-name: set_misc_286c_value
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_misc_286c_value                      <= FUN_00051038 @ 0x00051038
 * address symbols (name @ address):
 *   g_misc_286c_val                          @ 0x2000286c
 */
/* Reconstructed FUN_00051038 @ 0x51038  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void set_misc_286c_value(uint32_t param_1) {
    *(volatile uint32_t*)0x2000286cUL = param_1;
}
