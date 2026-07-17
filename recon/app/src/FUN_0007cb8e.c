/* Reconstructed k_msleep @ 0x0007cb8e from Zephyr kernel.h.
 * Raw backmap: FUN_0007cb8e@0x0007cb8e. */

#include <stdint.h>

/* GCC runtime division and the configured Zephyr sleep continuation. */
extern uint64_t FUN_0000e244(int32_t numerator_low, int32_t numerator_high,
                            uint32_t denominator_low, uint32_t denominator_high);
extern void thunk_FUN_00074844(uint32_t ticks_low, uint32_t ticks_high,
                              uint32_t preserved_divisor, uint32_t forwarded_r3);

void k_msleep(int32_t milliseconds, uint32_t unused_r1, uint32_t unused_r2,
              uint32_t forwarded_r3)
{
    uint64_t ticks = FUN_0000e244(milliseconds * 0x8000 + 999,
                                 milliseconds >> 17, 1000u, 0u);
    (void)unused_r1;
    (void)unused_r2;
    thunk_FUN_00074844((uint32_t)ticks, (uint32_t)(ticks >> 32),
                       1000u, forwarded_r3);
}
