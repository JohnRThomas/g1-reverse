/* readable reconstruction; identity: FUN_000826e0 @ 0x000826e0
 * public-name: atomic_or_0
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_or_0 @ 0x826e0  (CFG-directed candidate) */
#include <stdint.h>

/* Pinned Zephyr 3.4.99 atomic_builtin.h semantics. */
int atomic_or_0(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);
}
