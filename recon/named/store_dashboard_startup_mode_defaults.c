/* readable reconstruction; identity: FUN_00016574 @ 0x00016574
 * public-name: store_dashboard_startup_mode_defaults
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   store_dashboard_startup_mode_defaults    <= FUN_00016574 @ 0x00016574
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_00016574 @ 0x16574 (uncatalogued exact leaf entry). */

#include <stdint.h>

uint32_t store_dashboard_startup_mode_defaults(uint32_t value)
{
    *(volatile uint32_t *)0x2007fc00UL = value;
    return value;
}
