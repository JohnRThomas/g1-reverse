/* Reconstructed atomic_test_and_set_bit_0 @ 0x00082236 (FUN_00082236; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic.h. */
#include <stdbool.h>
#include <stdint.h>
bool atomic_test_and_set_bit_0(volatile int32_t *target, int bit)
{
    int32_t mask = (int32_t)1 << bit;
    return (__atomic_fetch_or(target, mask, __ATOMIC_SEQ_CST) & mask) != 0;
}
