#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081180 @ 0x00081180
 * public-name: atomic_and_1
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_and_1 @ 0x00081180 (FUN_00081180; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic_builtin.h. */
#include <stdint.h>
int32_t atomic_and_1(volatile int32_t *target, int32_t value)
{ return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST); }
