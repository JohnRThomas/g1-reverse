/* readable reconstruction; identity: FUN_00032c0c @ 0x00032c0c
 * public-name: arm_timeout_10s
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_timeout_10s                          <= FUN_00032c0c @ 0x00032c0c
 *   k_uptime_get_4                           <= FUN_0007d12e @ 0x0007d12e
 * address symbols (name @ address):
 *   g_deadline_10s                           @ 0x20004948
 */
/* Reconstructed FUN_00032c0c @ 0x32c0c  (parity: 300/300 trials, PROVEN) */

#ifdef G1_APP_SDK_INLINE_COHESION
#include <stdint.h>
extern int64_t z_impl_k_uptime_ticks(void);
/* Exact configured kernel.h/time_units.h owner: floor(ticks * 1000 / 32768). */
static __attribute__((always_inline)) inline long long g1_sdk_uptime_get_4(void)
{
    return (long long)(((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15);
}
#else
extern long long k_uptime_get_4(void); /* k_uptime_get_4 @ 0x0007d12e */
#define g1_sdk_uptime_get_4() k_uptime_get_4()
#endif

void arm_timeout_10s(void)
{
    long long lVar1 = g1_sdk_uptime_get_4();
    *(volatile long long*)0x20004948UL = lVar1 + 10000;
}
