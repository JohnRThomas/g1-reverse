#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007eb4e @ 0x0007eb4e
 * public-name: atomic_set
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_set @ 0x0007eb4e.
 * Raw/address back-map: FUN_0007eb4e / 0x0007eb4e.
 */
#include <stdint.h>

int32_t atomic_set(volatile int32_t *target, int32_t value)
{
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);
}
