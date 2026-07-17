#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e3dc @ 0x0004e3dc
 * public-name: settings_backend_ptr_store
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_backend_ptr_store               <= FUN_0004e3dc @ 0x0004e3dc
 * address symbols (name @ address):
 *   g_settings_nvs_backend                   @ 0x2000a100
 */
/* Reconstructed FUN_0004e3dc @ 0x4e3dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void settings_backend_ptr_store(uint32_t param_1) {
    *(volatile uint32_t*)((unsigned long)&g_settings_nvs_backend) /*=0x2000a100*/ = param_1;
}
