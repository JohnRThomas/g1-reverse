#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00049040 @ 0x00049040
 * public-name: getDelayExitValue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   getDelayExitValue                        <= FUN_00049040 @ 0x00049040
 * address symbols (name @ address):
 *   g_delayexitvalue                         @ 0x2000a094
 */
/* Reconstructed FUN_00049040 @ 0x49040  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint32_t getDelayExitValue(void) {
    return *(volatile uint32_t*)((unsigned long)&g_delayexitvalue) /*=0x2000a094*/;
}
