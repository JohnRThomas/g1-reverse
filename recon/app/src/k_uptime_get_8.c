/* Reconstructed k_uptime_get_8 @ 0x0007d382 from configured Zephyr 3.4.99 kernel.h.
 * Identity/backmap: FUN_0007d382.
 */
#include <stdint.h>

extern uint64_t uptime_ticks_get(void); /* FUN_00086698 @ 0x00086698 */

int64_t k_uptime_get_8(void)
{
    return (int64_t)((uptime_ticks_get() * UINT64_C(1000)) >> 15);
}
