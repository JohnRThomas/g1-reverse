/* Reconstructed atomic_inc @ 0x0007ee2c.
 * Raw/address back-map: FUN_0007ee2c / 0x0007ee2c.
 */
#include <stdint.h>

int32_t atomic_inc(volatile int32_t *target)
{
    return __atomic_fetch_add(target, 1, __ATOMIC_SEQ_CST);
}
