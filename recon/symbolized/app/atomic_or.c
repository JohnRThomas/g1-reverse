#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080e6a @ 0x00080e6a
 * public-name: atomic_or
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_or @ 0x80e6a  (CFG-directed candidate) */
#include <stdint.h>

/* Pinned Zephyr 3.4.99 atomic_builtin.h semantics. */
int atomic_or(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);
}
