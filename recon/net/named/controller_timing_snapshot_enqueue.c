/* readable reconstruction; identity: FUN_0100f300 @ 0x0100f300
 * public-name: controller_timing_snapshot_enqueue
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_snapshot_enqueue       <= FUN_0100f300 @ 0x0100f300
 */
/* net-core FUN_0100f300 @ 0x100f300  (CFG-directed candidate) */
/* net-core FUN_0100f300 @ 0x0100f300
 * Readable role: snapshot controller timing fields into a deferred packet-result node.
 * The entry tail-calls the shared packet-result enqueue suffix at 0x0100ef08.
 * Address back-map:
 *   packet-result callback = 0x0100f8a5 (literal at 0x0100f364)
 *   controller_packet_result_enqueue_suffix = internal entry 0x0100ef08
 */
#include <stdint.h>

extern void FUN_0100ef08(void *node, uintptr_t callback,
                         void *preserved_node, const void *preserved_state);
#define controller_packet_result_enqueue_suffix FUN_0100ef08

static uint16_t load_u16(const volatile uint8_t *base, unsigned int offset)
{
    return *(const volatile uint16_t *)(base + offset);
}

static void store_u16(volatile uint8_t *base, unsigned int offset,
                      uint16_t value)
{
    *(volatile uint16_t *)(base + offset) = value;
}

void controller_timing_snapshot_enqueue(uint16_t packet_id, const void *controller_state,
                  void *work_node)
{
    const volatile uint8_t *state =
        (const volatile uint8_t *)controller_state;
    volatile uint8_t *node = (volatile uint8_t *)work_node;
    uint16_t duration = load_u16(state, 0x0c);
    uint16_t interval = load_u16(state, 0x08);
    uint16_t prior_end = load_u16(state, 0x2e);
    uint16_t start = load_u16(state, 0x0a);
    uint16_t end = load_u16(state, 0x0e);
    uint8_t changed;

    store_u16(node, 0x09, packet_id);
    store_u16(node, 0x0b, interval);
    store_u16(node, 0x0d, duration);
    store_u16(node, 0x0f, start);
    store_u16(node, 0x11, end);

    changed = (prior_end != end ||
               load_u16(state, 0x2a) != start ||
               load_u16(state, 0x30) != duration ||
               load_u16(state, 0x2c) != interval) ? 1U : 0U;
    node[0x13] = (uint8_t)((node[0x13] & 0xfeU) | changed);

    store_u16((volatile uint8_t *)state, 0x2a, start);
    store_u16((volatile uint8_t *)state, 0x2e, end);
    store_u16((volatile uint8_t *)state, 0x2c, interval);
    store_u16((volatile uint8_t *)state, 0x30, duration);

    controller_packet_result_enqueue_suffix((void *)node, 0x0100f8a5U,
                                             (void *)node,
                                             (const void *)state);
}
