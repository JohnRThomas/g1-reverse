/* net-core FUN_01019f9c @ 0x01019f9c */
#include <stdint.h>
#include <stddef.h>

extern uint32_t FUN_0100e04c(const uint8_t *packet);
extern uint32_t FUN_0100e064(const uint8_t *packet);
extern void *FUN_01025a84(void *destination, int value, size_t length);

void FUN_01019f9c(const uint8_t *packet, volatile uint8_t *decoded)
{
    uint32_t packet_length = packet[3] & 0x3fu;
    uint32_t flags;
    uint32_t offset;
    const uint8_t *cursor;

    if (packet_length == 0) {
        FUN_01025a84((void *)decoded, 0, 0x28u);
        return;
    }

    decoded[0x11] = (uint8_t)FUN_0100e04c(packet);
    decoded[0x12] = (uint8_t)FUN_0100e064(packet);
    flags = packet[4];
    decoded[1] = (uint8_t)flags;
    decoded[0] = packet[3] >> 6;

    if ((flags & 1u) != 0) {
        offset = 11;
        cursor = packet + 5;
    } else {
        offset = 5;
        cursor = 0;
    }
    *(const uint8_t * volatile *)(decoded + 4) = cursor;

    cursor = 0;
    if ((flags & 2u) != 0) {
        cursor = packet + offset;
        offset = (flags & 1u) != 0 ? 17u : 11u;
    }
    *(const uint8_t * volatile *)(decoded + 8) = cursor;
    if ((flags & 4u) != 0) {
        offset = (uint8_t)(offset + 1u);
    }

    cursor = 0;
    if ((flags & 8u) != 0) {
        cursor = packet + offset;
        offset = (uint8_t)(offset + 2u);
    }
    *(const uint8_t * volatile *)(decoded + 0x14) = cursor;

    cursor = 0;
    if ((flags & 0x10u) != 0) {
        cursor = packet + offset;
        offset = (uint8_t)(offset + 3u);
    }
    *(const uint8_t * volatile *)(decoded + 0x18) = cursor;

    cursor = 0;
    if ((flags & 0x20u) != 0) {
        cursor = packet + offset;
        offset = (uint8_t)(offset + 18u);
    }
    *(const uint8_t * volatile *)(decoded + 0x1c) = cursor;

    cursor = 0;
    if ((flags & 0x40u) != 0) {
        cursor = packet + offset;
        offset = (uint8_t)(offset + 1u);
    }
    *(const uint8_t * volatile *)(decoded + 0x20) = cursor;

    uint32_t remainder = (uint8_t)(packet_length + 4u - offset);
    *(const uint8_t * volatile *)(decoded + 0x24) =
        remainder != 0 ? packet + offset : 0;
    decoded[0x10] = (uint8_t)(packet[1] - 1u - packet_length);
    *(const uint8_t * volatile *)(decoded + 0x0c) =
        decoded[0x10] != 0 ? packet + offset + remainder : 0;
}
