/* readable reconstruction; identity: FUN_000826f6 @ 0x000826f6
 * public-name: atomic_and_4
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_and_4 @ 0x000826f6 from Zephyr atomic_builtin.h.
 * Raw backmap: FUN_000826f6@0x000826f6. */

#include <stdint.h>
int32_t atomic_and_4(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}
