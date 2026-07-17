/* Reconstructed FUN_00028964 @ 0x28964
 * CFG_VERIFY_CALL_ARITIES=1,0,0,0,0,0,1
 * Readable identity: enter_active_click_mode.
 * Raw/address backmap: enter_active_click_mode <= FUN_00028964 @ 0x00028964.
 */

#include <stdint.h>

extern void FUN_0001694c(uint32_t mode);
extern uint8_t *FUN_000167a8(void);
extern void FUN_0002bdf0(void);
extern void FUN_0007d874(uint32_t mode);

void FUN_00028964(void)
{
    volatile uint8_t *const pending_reset =
        (volatile uint8_t *)0x2001b811UL;
    volatile uint8_t *const click_mode_active =
        (volatile uint8_t *)0x20018d8bUL;
    uint8_t *device_state;

    if (*pending_reset != 0U) {
        *pending_reset = 0U;
    }

    FUN_0001694c(2U);
    (void)FUN_000167a8();
    FUN_0002bdf0();

    device_state = FUN_000167a8();
    device_state[0xee4] = 2U;
    device_state = FUN_000167a8();
    device_state[0x0d5] = 3U;
    device_state = FUN_000167a8();
    FUN_0007d874(device_state[0x0d5]);

    *click_mode_active = 1U;
}
