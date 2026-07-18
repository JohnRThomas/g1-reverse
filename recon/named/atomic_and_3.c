/* readable reconstruction; identity: FUN_00080ea8 @ 0x00080ea8
 * public-name: atomic_and_3
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_and_3 @ 0x00080ea8 (FUN_00080ea8; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic_builtin.h. */
#include <stdint.h>
int32_t atomic_and_3(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}
