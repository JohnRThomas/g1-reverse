/* readable reconstruction; identity: FUN_0007cb54 @ 0x0007cb54
 * public-name: atomic_or_bit1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_or_bit1                           <= FUN_0007cb54 @ 0x0007cb54
 */
/* Reconstructed FUN_0007cb54 @ 0x7cb54 */
#include <stdint.h>

void atomic_or_bit1(volatile uint32_t *flags)
{
    __atomic_fetch_or(flags, 2u, __ATOMIC_RELAXED);
}
