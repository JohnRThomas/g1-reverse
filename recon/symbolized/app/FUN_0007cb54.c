#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cb54 @ 0x0007cb54
 * public-name: FUN_0007cb54
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_0007cb54 @ 0x7cb54 */
#include <stdint.h>

void FUN_0007cb54(volatile uint32_t *flags)
{
    __atomic_fetch_or(flags, 2u, __ATOMIC_RELAXED);
}
