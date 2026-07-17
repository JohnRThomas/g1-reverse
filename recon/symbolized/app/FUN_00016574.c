#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016574 @ 0x00016574
 * public-name: FUN_00016574
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_00016574 @ 0x16574 (uncatalogued exact leaf entry). */

#include <stdint.h>

uint32_t FUN_00016574(uint32_t value)
{
    *(volatile uint32_t *)((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ = value;
    return value;
}
