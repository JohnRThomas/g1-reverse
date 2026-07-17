/* readable reconstruction; identity: FUN_01026c94 @ 0x01026c94
 * public-name: controller_packet_payload_extract
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_payload_extract        <= FUN_01026c94 @ 0x01026c94
 */
/* net-core FUN_01026c94 @ 0x1026c94  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_01026912(uint32_t header, uint32_t kind);
extern void FUN_01025998(void *destination, const void *source, uint32_t length);
extern void FUN_0100951c(void *packet, void *header);
/* Readable role: controller_packet_payload_extract. Raw back-map: FUN_01026c94 @ 0x01026c94. */
uint16_t controller_packet_payload_extract(void *packet_pointer, void *destination)
{
    uint8_t *packet = (uint8_t *)packet_pointer;
    uint16_t header = *(uint16_t *)(packet + 8);
    uint16_t payload_offset = (uint16_t)(header & 0x7fffu);
    uint8_t *payload = packet + 0x18;
    uint16_t result;
    if (FUN_01026912(header, *(uint16_t *)(packet + 4)) != 0u)
        return 0u;
    if (destination != 0)
        FUN_01025998(destination, payload + payload_offset + 2u, packet[0x13]);
    result = *(uint16_t *)(payload + payload_offset);
    FUN_0100951c(packet, packet + 8);
    return result;
}
