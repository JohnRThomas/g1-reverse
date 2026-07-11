/* Reconstructed FUN_0007cb54 @ 0x7cb54 */
#include <stdint.h>

void FUN_0007cb54(volatile uint32_t *flags)
{
    __atomic_fetch_or(flags, 2u, __ATOMIC_RELAXED);
}
