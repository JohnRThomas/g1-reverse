/* Reconstructed k_uptime_get_10 @ 0x0007daa4 from configured Zephyr 3.4.99 kernel.h.
 * Identity/backmap: FUN_0007daa4.
 */
#include <stdint.h>

extern uint64_t uptime_ticks_get(void); /* FUN_00086698 @ 0x00086698 */

int64_t k_uptime_get_10(void)
{
    return (int64_t)((uptime_ticks_get() * UINT64_C(1000)) >> 15);
}
