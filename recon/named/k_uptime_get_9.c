/* readable reconstruction; identity: FUN_0007d9a4 @ 0x0007d9a4
 * public-name: k_uptime_get_9
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed k_uptime_get_9 @ 0x0007d9a4 from configured Zephyr 3.4.99 kernel.h.
 * Identity/backmap: FUN_0007d9a4.
 */
#include <stdint.h>

extern uint64_t uptime_ticks_get(void); /* FUN_00086698 @ 0x00086698 */

int64_t k_uptime_get_9(void)
{
    return (int64_t)((uptime_ticks_get() * UINT64_C(1000)) >> 15);
}
