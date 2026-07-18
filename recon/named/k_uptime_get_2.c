/* readable reconstruction; identity: FUN_0007ce40 @ 0x0007ce40
 * public-name: k_uptime_get_2
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed k_uptime_get_2 @ 0x0007ce40 from Zephyr kernel.h.
 * Raw backmap: FUN_0007ce40@0x0007ce40. */

#include <stdint.h>
extern uint64_t uptime_ticks_get(void); /* FUN_00086698@0x00086698 */
int64_t k_uptime_get_2(void)
{
    return (int64_t)((uptime_ticks_get() * UINT64_C(1000)) >> 15);
}
