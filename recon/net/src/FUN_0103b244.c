/* Zephyr work-queue flag_test_and_clear @ 0x0103b244,
 * exact extent 0x16.
 * Raw/address backmap: FUN_0103b244@0x0103b244. */
#include <stdbool.h>
#include <stdint.h>
#define flag_test_and_clear FUN_0103b244

bool flag_test_and_clear(uint32_t *flags, uint32_t bit)
{
    uint32_t prior = *flags;

    *flags = prior & ~(1u << bit);
    return ((prior >> bit) & 1u) != 0u;
}
