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
extern long long FUN_0007d12e(void); /* k_uptime_get_4 @ 0x0007d12e */
#define g1_sdk_uptime_get_4() FUN_0007d12e()
#endif

void FUN_00032c0c(void)
{
    long long lVar1 = g1_sdk_uptime_get_4();
    *(volatile long long*)0x20004948UL = lVar1 + 10000;
}
