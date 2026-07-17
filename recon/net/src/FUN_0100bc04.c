/* net-core controller_indexed_state_byte_get @ 0x0100bc04.
 * Raw backmap: FUN_0100bc04@0x0100bc04. */
#include <stdint.h>

uint32_t FUN_0100bc04(uint32_t index)
{
    volatile uint8_t *controller_state =
        (volatile uint8_t *)0x21000d18u;

    if (index >= controller_state[1]) {
        return 0;
    }
    return controller_state[0x142u + index];
}
