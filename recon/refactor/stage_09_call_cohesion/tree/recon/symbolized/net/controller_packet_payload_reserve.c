#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01026e48 @ 0x01026e48
 * public-name: controller_packet_payload_reserve
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_overhead_span_get      <= FUN_01026856 @ 0x01026856
 *   controller_packet_payload_reserve        <= FUN_01026e48 @ 0x01026e48
 */
/* net-core controller_packet_payload_reserve @ 0x01026e48.
 * Raw backmap: FUN_01026e48@0x01026e48. */
#include <stdint.h>

extern int32_t FUN_010268ce(uint32_t, uint32_t);
extern uint32_t controller_packet_overhead_span_get(uint32_t);

uint32_t controller_packet_payload_reserve(uint16_t *packet, uint16_t requested)
{
    uint32_t upper_offset = packet[4] & 0x7fffu;
    uint32_t lower_offset = packet[3] & 0x7fffu;
    uint32_t available;

    if (FUN_010268ce(packet[4], packet[3]) != 0) {
        packet[8] = 0;
        return 0;
    }

    available = packet[0];
    if (available < 0x45u) {
        available = 0x45u;
    }
    if (lower_offset < upper_offset) {
        uint32_t bounded = upper_offset - lower_offset -
            controller_packet_overhead_span_get(*((uint8_t *)packet + 0x13));
        if ((int32_t)bounded <= (int32_t)available) {
            available = bounded;
        }
    }
    if (packet[6] != 0) {
        available -= *(uint16_t *)((uint8_t *)packet + lower_offset + 0x18u);
    }
    if ((int32_t)available < (int32_t)(uint32_t)requested) {
        packet[8] = 0;
        return 0;
    }

    uint32_t payload = (uint32_t)(uintptr_t)(
        (uint8_t *)packet + 0x18u + lower_offset +
        controller_packet_overhead_span_get(*((uint8_t *)packet + 0x13)) + packet[6] - 3u);
    packet[8] = requested;
    return payload;
}
