/* Reconstructed atomic_set @ 0x0007eb4e.
 * Raw/address back-map: FUN_0007eb4e / 0x0007eb4e.
 */
#include <stdint.h>

int32_t atomic_set(volatile int32_t *target, int32_t value)
{
    return __atomic_exchange_n(target, value, __ATOMIC_SEQ_CST);
}
