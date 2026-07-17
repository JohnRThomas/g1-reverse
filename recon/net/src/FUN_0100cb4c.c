/* net-core controller_packet_config_apply_if_active @ 0x0100cb4c.
 * Raw backmap: FUN_0100cb4c@0x0100cb4c. */
#include <stdint.h>

extern void FUN_0101fc40(uint32_t, uint32_t, uint32_t);

uint32_t FUN_0100cb4c(uint32_t packet_value)
{
    volatile uint8_t *controller_state =
        (volatile uint8_t *)0x21000d18u;
    uint32_t active = controller_state[0x18a];

    if (active != 0) {
        uint32_t count = controller_state[1];
        if (count != 0) {
            FUN_0101fc40(0x21000d1au, count, packet_value);
        } else {
            active = 0;
        }
    }
    return active;
}
