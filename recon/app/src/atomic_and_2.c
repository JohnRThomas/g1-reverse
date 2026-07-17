/* Reconstructed atomic_and_2 @ 0x813b4  (CFG-directed candidate) */
#include <stdint.h>

/* Pinned Zephyr 3.4.99 atomic_builtin.h semantics. */
int atomic_and_2(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}
