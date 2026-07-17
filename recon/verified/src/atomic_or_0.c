/* Reconstructed atomic_or_0 @ 0x826e0  (CFG-directed candidate) */
#include <stdint.h>

/* Pinned Zephyr 3.4.99 atomic_builtin.h semantics. */
int atomic_or_0(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_or(target, value, __ATOMIC_SEQ_CST);
}
