/* Reconstructed pin_is_output @ 0x00065494 from configured NCS 2.5.1 nrfx_gpiote.c.
 * Identity/backmap: FUN_00065494.
 */
#include <stdbool.h>
#include <stdint.h>

extern uint32_t get_pin_idx(uint32_t pin); /* FUN_00065434 @ 0x00065434 */

bool pin_is_output(uint32_t pin)
{
    volatile const uint16_t *pin_flags =
        (volatile const uint16_t *)(uintptr_t)0x20002bc0;
    return (pin_flags[get_pin_idx(pin) + 8u] & UINT16_C(0x02)) != 0u;
}
