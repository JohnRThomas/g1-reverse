#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e474 @ 0x0004e474
 * public-name: settings_store_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_store_init                      <= FUN_0004e474 @ 0x0004e474
 * address symbols (name @ address):
 *   g_settings_stores                        @ 0x2000a104
 */
/* Reconstructed FUN_0004e474 @ 0x4e474
 * Readable identity: settings_store_init.
 * Raw/address backmap: settings_store_init <= FUN_0004e474 @ 0x0004e474.
 */

#include <stdint.h>

void settings_store_init(void)
{
    volatile uint32_t *const settings_load_srcs =
        (volatile uint32_t *)((unsigned long)&g_settings_stores) /*=0x2000a104*/;

    settings_load_srcs[0] = 0U;
    settings_load_srcs[1] = 0U;
}
