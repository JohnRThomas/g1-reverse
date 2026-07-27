/* Reconstructed atomic_clear_bit_0 @ 0x00081e14 (FUN_00081e14; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic.h. */
#include <stdint.h>
void atomic_clear_bit_0(volatile int*target, int bit) { (void)__atomic_fetch_and(target, ~((int32_t)1 << bit), __ATOMIC_SEQ_CST); }
