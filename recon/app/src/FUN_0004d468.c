/* Reconstructed FUN_0004d468 @ 0x4d468
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: z_log_dropped.
 * Raw/address backmap: z_log_dropped <= FUN_0004d468 @ 0x0004d468.
 */

#include <stdint.h>

extern uint32_t FUN_0007ee2c(volatile uint32_t *value); /* atomic_inc */

uint32_t FUN_0004d468(uint32_t buffered)
{
    uint32_t previous =
        FUN_0007ee2c((volatile uint32_t *)0x2000a0d4UL);

    if (buffered != 0U) {
        (void)__atomic_fetch_sub((uint32_t *)0x2000a0d8UL, 1U,
                                 __ATOMIC_SEQ_CST);
    }
    return previous;
}
