/* Reconstructed z_log_dropped @ 0x0102de10.
 * Raw/address back-map: FUN_0102de10 / 0x0102de10.
 */
#include <stdint.h>
extern void FUN_0103a294(volatile uint32_t *value); /* atomic_inc */

void FUN_0102de10(uint32_t buffered)
{
    volatile uint32_t *const buffered_count =
        (volatile uint32_t *)0x21004668u;
    FUN_0103a294((volatile uint32_t *)0x21004664u);
    if (buffered != 0u) {
        (void)__atomic_fetch_sub((uint32_t *)buffered_count, 1u,
                                 __ATOMIC_SEQ_CST);
    }
}
