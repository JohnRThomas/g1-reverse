/* Reconstructed atomic_and @ 0x0007c08e (FUN_0007c08e; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic_builtin.h. */
#include <stdint.h>
int32_t atomic_and(volatile int32_t *target, int32_t value)
{
    return __atomic_fetch_and(target, value, __ATOMIC_SEQ_CST);
}
