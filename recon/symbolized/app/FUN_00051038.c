#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051038 @ 0x00051038
 * public-name: FUN_00051038
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_misc_286c_val                          @ 0x2000286c
 */
/* Reconstructed FUN_00051038 @ 0x51038  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00051038(uint32_t param_1) {
    *(volatile uint32_t*)((unsigned long)&g_misc_286c_val) /*=0x2000286c*/ = param_1;
}
