/* FUN_010269ce @ 0x010269ce: reserve payload space in a packed controller packet. */
#include <stdint.h>

extern uint32_t FUN_010268ce(uint32_t end_cursor, uint32_t begin_cursor);
extern uint32_t FUN_01026856(uint32_t packet_type);
extern void FUN_01008d00(uint32_t file_id, uint32_t line);
#define controller_packet_overhead_span_get FUN_01026856
#define sdc_assertion_fail FUN_01008d00

void *controller_packet_payload_reserve(uint8_t *packet, uint32_t requested_length_argument)
{
    uint16_t requested_length = (uint16_t)requested_length_argument;
    uint16_t begin_header = *(uint16_t *)(packet + 6);
    uint16_t end_header = *(uint16_t *)(packet + 8);
    uint16_t begin = begin_header & 0x7fffu;
    uint16_t end = end_header & 0x7fffu;
    uint32_t minimum = *(uint16_t *)packet;
    if (minimum < 0x45u) {
        minimum = 0x45u;
    }
    if (requested_length > minimum) {
        sdc_assertion_fail(0x14u, 0xc6u);
    }
    if (FUN_010268ce(end_header, begin_header) != 0u) {
        return 0;
    }
    if (begin < end &&
        (int32_t)((uint32_t)(end - begin) -
                  controller_packet_overhead_span_get(packet[0x13])) <
            (int32_t)requested_length) {
        packet[0x12] = 0u;
        return 0;
    }
    uint8_t *payload = packet + 0x18u + begin;
    *(uint16_t *)payload = (uint16_t)requested_length;
    packet[0x12] = 1u;
    return payload;
}

/* Raw identity/back-map: FUN_010269ce @ 0x010269ce, true extent 0xb0. */
extern __typeof(controller_packet_payload_reserve) FUN_010269ce
    __attribute__((alias("controller_packet_payload_reserve")));
