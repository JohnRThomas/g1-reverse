#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e3dc @ 0x0004e3dc
 * public-name: settings_dst_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_dst_register                    <= FUN_0004e3dc @ 0x0004e3dc
 * address symbols (name @ address):
 *   g_settings_nvs_backend                   @ 0x2000a100
 */
/* Reconstructed FUN_0004e3dc @ 0x4e3dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
struct settings_store_recon;
void settings_dst_register(struct settings_store_recon *store) {
    *(struct settings_store_recon * volatile *)((unsigned long)&g_settings_nvs_backend) /*=0x2000a100*/ = store;
}
