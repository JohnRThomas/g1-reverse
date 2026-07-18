/* Cohesive-link bridges for firmware identities emitted from Zephyr headers.
 *
 * These symbols are not separate upstream archive owners.  Recovered callers
 * that predate source cohesion may still contain a BL to the compiler-outlined
 * header body, so expose only that historical identity at the integration
 * boundary.  Canonical parity sources remain untouched.
 */
#include <stdint.h>

extern int64_t z_impl_k_uptime_ticks(void);

/* FUN_0007d12e / k_uptime_get_4.
 * Pinned NCS 2.5.1 Zephyr kernel.h:1736 and time_units.h implement
 * floor(ticks * 1000 / CONFIG_SYS_CLOCK_TICKS_PER_SEC); the recovered config
 * has CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768.  This caller-visible identity
 * returns the low ABI word, exactly as aging_mode_thread consumes it.
 */
uint32_t k_uptime_get_4(void)
{
    return (uint32_t)(((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15);
}
