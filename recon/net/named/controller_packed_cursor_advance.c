/* readable reconstruction; identity: FUN_0100951c @ 0x0100951c
 * public-name: controller_packed_cursor_advance
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packed_cursor_advance         <= FUN_0100951c @ 0x0100951c
 *   controller_packet_overhead_span_get      <= FUN_01026856 @ 0x01026856
 */
/* net-core FUN_0100951c @ 0x100951c  (CFG-directed candidate) */
/* net-core FUN_0100951c @ 0x0100951c
 * Readable role: advance a packed controller buffer cursor and update its wrap flag.
 * Address back-map:
 *   controller_packet_overhead_span_get = FUN_01026856 @ 0x01026856
 *   packed cursor wrap flag = 0x8000 (literal at 0x010095bc)
 */
#include <stdint.h>

extern uint32_t controller_packet_overhead_span_get(uint32_t packet_kind);
#define controller_packet_overhead_span_get controller_packet_overhead_span_get

void controller_packed_cursor_advance(const void *layout, uint16_t *packed_cursor)
{
    const uint8_t *bytes = (const uint8_t *)layout;
    uint16_t original = *packed_cursor;
    uint16_t offset = original & 0x7fffU;
    uint16_t overhead =
        (uint16_t)controller_packet_overhead_span_get(bytes[0x13]);
    uint16_t quantum = (uint16_t)(*(const uint16_t *)bytes + overhead);
    uint32_t numerator = (uint32_t)quantum +
                         *(const uint16_t *)(bytes + 0x18 + offset) +
                         (uint32_t)overhead - 1U;
    uint16_t blocks = (uint16_t)((int32_t)numerator / (int32_t)quantum);
    uint16_t next = (uint16_t)(offset + (uint16_t)(quantum * blocks));

    if (next < *(const uint16_t *)(bytes + 2)) {
        next = (uint16_t)(next | (original & 0x8000U));
    } else {
        next = (uint16_t)((~original) & 0x8000U);
    }
    *packed_cursor = next;
}
