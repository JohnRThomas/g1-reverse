/* net-core controller_indexed_status_byte_get @ 0x0100bbec.
 * Raw/address backmap: FUN_0100bbec@0x0100bbec. */
#include <stdint.h>
#define controller_indexed_status_byte_get FUN_0100bbec

uint32_t controller_indexed_status_byte_get(uint32_t index)
{
    volatile const uint8_t * const controller_state =
        (volatile const uint8_t *)0x21000d18u;

    if (index >= controller_state[1]) {
        return 0;
    }
    return controller_state[0x14au + index];
}
