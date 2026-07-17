/* Reconstructed atomic_clear_bit_1 @ 0x0008304c (FUN_0008304c; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic.h. */
#include <stdint.h>
void atomic_clear_bit_1(volatile int32_t *target, int bit)
{
    (void)__atomic_fetch_and(target, ~((int32_t)1 << bit), __ATOMIC_SEQ_CST);
}
