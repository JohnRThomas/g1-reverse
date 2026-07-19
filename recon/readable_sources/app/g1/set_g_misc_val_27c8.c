#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004b1c0 @ 0x0004b1c0
 * public-name: set_g_misc_val_27c8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_g_misc_val_27c8                      <= FUN_0004b1c0 @ 0x0004b1c0
 * address symbols (name @ address):
 *   g_misc_val_27c8                          @ 0x200027c8
 */
/* Reconstructed FUN_0004b1c0 @ 0x4b1c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void set_g_misc_val_27c8(uint32_t param_1) {
    *(volatile uint32_t*)((unsigned long)&g_misc_val_27c8) /*=0x200027c8*/ = param_1;
}
