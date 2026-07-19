#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d33a @ 0x0007d33a
 * public-name: k_uptime_get_6
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed k_uptime_get_6 @ 0x0007d33a from configured Zephyr 3.4.99 kernel.h.
 * Identity/backmap: FUN_0007d33a.
 */
#include <stdint.h>

extern uint64_t uptime_ticks_get(void); /* FUN_00086698 @ 0x00086698 */

int64_t k_uptime_get_6(void)
{
    return (int64_t)((uptime_ticks_get() * UINT64_C(1000)) >> 15);
}
