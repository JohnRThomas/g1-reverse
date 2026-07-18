/* FUN_01026dae @ 0x01026dae: check whether another packed packet item is available. */
#include <stdint.h>

extern uint32_t FUN_01026912(uint32_t cursor, uint32_t end_cursor);
extern void controller_packed_cursor_advance(void *packet, uint16_t *cursor);

uint32_t controller_packet_has_next(uint8_t *packet)
{
    uint16_t end_cursor = *(uint16_t *)(packet + 6);
    uint16_t cursor = *(uint16_t *)(packet + 4);
    uint16_t offset = cursor & 0x7fffu;
    uint16_t *item = (uint16_t *)(packet + 0x18u + offset);
    if (FUN_01026912(cursor, end_cursor) != 0u) {
        return 0u;
    }
    if ((uint32_t)*(uint16_t *)(packet + 0x0e) +
            (uint32_t)*(uint16_t *)(packet + 0x0a) <
        *item) {
        return 1u;
    }
    controller_packed_cursor_advance(packet, &cursor);
    return FUN_01026912(cursor, end_cursor) == 0u;
}

/* Raw identity/back-map: FUN_01026dae @ 0x01026dae, true extent 0x9a. */
extern __typeof(controller_packet_has_next) FUN_01026dae
    __attribute__((alias("controller_packet_has_next")));
