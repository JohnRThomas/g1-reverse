/* readable reconstruction; identity: FUN_01026f32 @ 0x01026f32
 * public-name: sdc_buffer_accumulate
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_overhead_span_get      <= FUN_01026856 @ 0x01026856
 *   sdc_buffer_accumulate                    <= FUN_01026f32 @ 0x01026f32
 */
/* net-core FUN_01026f32 @ 0x1026f32  (CFG-directed candidate) */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t reason, uint32_t location);
/* Back-map: sdc_assertion_fail <= FUN_01008d00 @ 0x01008d00. */
extern void FUN_0100951c(void *state, void *descriptor);
extern void FUN_01025998(void *destination, const void *source, uint32_t length);
extern uint32_t controller_packet_overhead_span_get(uint8_t mode);

static inline uint16_t read_u16(const uint8_t *address)
{
    return *(const uint16_t *)address;
}

static inline void write_u16(uint8_t *address, uint16_t value)
{
    *(uint16_t *)address = value;
}

/* Raw back-map: FUN_01026f32 @ 0x01026f32, exact extent 0x112 bytes. */
uint32_t sdc_buffer_accumulate(uint8_t *state, uint32_t amount_argument,
                     uint32_t complete_argument)
{
    volatile uint16_t amount_storage = (uint16_t)amount_argument;
    volatile uint8_t complete_storage = (uint8_t)complete_argument;
    uint16_t amount = amount_storage;
    uint8_t complete = complete_storage;
    uint8_t *const payload = state + 0x18;
    uint16_t payload_offset = read_u16(state + 6) & 0x7fffu;
    uint8_t *const cursor = payload + payload_offset;
    uint16_t available = read_u16(state + 0x10);

    if ((available == 0) || (amount > available)) {
        return 0;
    }

    uint16_t accumulated = read_u16(state + 0x0c);
    if (accumulated == 0) {
        cursor[0] = 0;
        cursor[1] = 0;
    } else {
        if (read_u16(cursor) != accumulated) {
            sdc_assertion_fail(0x14u, 0x204u);
        }
        uint32_t trailer_offset = controller_packet_overhead_span_get(state[0x13]);
        const uint8_t *source = payload + payload_offset + accumulated +
                                trailer_offset - 3u;
        FUN_01025998(source, state + 0x14, 3u);
    }

    accumulated = (uint16_t)(accumulated + amount);
    write_u16(state + 0x0c, accumulated);
    write_u16(cursor, (uint16_t)(read_u16(cursor) + amount));

    if (complete != 0) {
        FUN_0100951c(state, state + 6);
        write_u16(state + 0x0c, 0);
    } else {
        uint32_t trailer_offset = controller_packet_overhead_span_get(state[0x13]);
        const uint8_t *source = payload + payload_offset + accumulated +
                                trailer_offset - 3u;
        FUN_01025998(state + 0x14, source, 3u);
    }

    write_u16(state + 0x10, 0);
    return 1;
}
