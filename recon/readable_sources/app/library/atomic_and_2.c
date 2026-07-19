#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000813b4 @ 0x000813b4
 * public-name: atomic_and_2
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_and_2 @ 0x813b4  (CFG-directed candidate) */
#include <stdint.h>

/* Pinned Zephyr 3.4.99 atomic_builtin.h semantics. */
int atomic_and_2(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}
