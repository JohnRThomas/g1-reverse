#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00021334 @ 0x00021334
 * public-name: build_status_notify_packet
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ble_xfer_seq_prev                      @ 0x20018d99
 *   g_ble_xfer_seq_cur                       @ 0x20018d9a
 */
/* Recovered build_status_notify_packet <= FUN_00021334 @ 0x00021334.
 *
 * The raw entry-point spelling is retained for the parity/link pipeline while
 * the implementation uses the protocol-facing name.  Address and callee
 * back-mapping live in recon/catalogs/function_names_app.json.
 */
#include <stdint.h>

extern void memset_bytes(void *destination, int value, int length);
extern uint8_t get_glassbox_charge_status(void);   /* FUN_00032784 @ 0x32784 */
extern uint8_t get_glassbox_charge_percent(void);  /* FUN_000327c4 @ 0x327c4 */

typedef int (*status_packet_sink_fn)(const void *packet, uint32_t length);

/* Only the fields owned by this routine are named.  The object passed by the
 * BLE dispatcher is much larger and is shared with the PUT/GET handlers. */
enum status_context_offset {
    STATUS_SINK_OFFSET                 = 0x000c,
    STATUS_RIGHT_TRANSFER_ID_OFFSET    = -0x06b0,
    STATUS_LEFT_TRANSFER_ID_OFFSET     = -0x06af,
    STATUS_BRIGHTNESS_LEVEL_OFFSET     = 0x0759,
    STATUS_BOX_STATE_OFFSET            = 0x0844,
    STATUS_BOX_STATE_VARIANT_OFFSET    = 0x0846,
};

enum status_query_selector {
    STATUS_QUERY_ECHO                  = 0x09,
    STATUS_QUERY_BOX_STATE             = 0x0a,
    STATUS_QUERY_BOX_CHARGE_STATE      = 0x0e,
    STATUS_QUERY_BOX_CHARGE_PERCENT    = 0x0f,
    STATUS_QUERY_BRIGHTNESS_LEVEL      = 0x12,
    STATUS_QUERY_C9_0D                 = 0xf0,
    STATUS_QUERY_C9_0F                 = 0xf1,
    STATUS_QUERY_C9_4E                 = 0xf2,
};

typedef struct __attribute__((packed)) {
    uint16_t response_code;
    uint8_t value;
    uint8_t transfer_sequence;
    uint8_t previous_transfer_sequence;
    uint8_t reserved[16];
} status_notify_packet_t;

static volatile uint8_t *const ble_xfer_seq_prev_reg =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_ble_xfer_seq_prev) /*=0x20018d99*/; /* original literal @ 0x2145c */
static volatile uint8_t *const ble_xfer_seq_cur_reg =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_ble_xfer_seq_cur) /*=0x20018d9a*/; /* original literal @ 0x21458 */

static inline uint8_t status_context_byte(const void *context, int offset)
{
    return *((const uint8_t *)context + offset);
}

static inline status_packet_sink_fn status_context_sink(const void *context)
{
    return *(status_packet_sink_fn const *)
        ((const uint8_t *)context + STATUS_SINK_OFFSET);
}

/* The box-state byte uses 0x5d..0x60 as internal states.  The wire protocol
 * separates the two transitional states with the adjacent variant flag and
 * folds every later state into 0x64. */
static uint8_t encode_box_state(const void *context)
{
    uint8_t state = status_context_byte(context, STATUS_BOX_STATE_OFFSET);
    uint8_t variant =
        status_context_byte(context, STATUS_BOX_STATE_VARIANT_OFFSET);

    if (state == 0x5d)
        return variant == 0 ? 0x5e : 0x5f;
    if (state == 0x5e)
        return variant == 0 ? 0x60 : 0x61;
    if (state == 0x5f)
        return 0x62;
    if (state == 0x60)
        return 0x63;
    if (state > 0x60)
        return 0x64;
    return state;
}

uint32_t build_status_notify_packet(void *context,
                                    const uint8_t *request)
{
    status_notify_packet_t packet;
    uint8_t selector;

    /* The firmware clears the first word separately, then the remaining
     * seventeen transmitted bytes through its byte memset helper. */
    *(uint32_t *)(void *)&packet = 0;
    memset_bytes((uint8_t *)&packet + 4, 0, 17);

    selector = request[1];
    if (selector > STATUS_QUERY_BRIGHTNESS_LEVEL) {
        switch (selector) {
        case STATUS_QUERY_C9_0F:
            packet.response_code = 0xc90f;
            packet.value = status_context_byte(
                context, STATUS_RIGHT_TRANSFER_ID_OFFSET);
            break;
        case STATUS_QUERY_C9_4E:
            packet.response_code = 0xc94e;
            packet.value = status_context_byte(
                context, STATUS_RIGHT_TRANSFER_ID_OFFSET);
            break;
        case STATUS_QUERY_C9_0D:
            packet.response_code = 0xc90d;
            packet.value = status_context_byte(
                context, STATUS_LEFT_TRANSFER_ID_OFFSET);
            break;
        default:
            packet.response_code = (uint16_t)(0x00f5u |
                                              ((uint16_t)selector << 8));
            goto publish;
        }

        packet.transfer_sequence = *ble_xfer_seq_cur_reg;
        *ble_xfer_seq_cur_reg = 0;
        packet.previous_transfer_sequence = *ble_xfer_seq_prev_reg;
        *ble_xfer_seq_prev_reg = 0;
        goto publish;
    }

    switch (selector) {
    case STATUS_QUERY_ECHO:
        packet.response_code = *(const uint16_t *)(const void *)request;
        packet.value = request[2];
        break;
    case STATUS_QUERY_BOX_STATE:
        packet.response_code = 0x0af5;
        packet.value = encode_box_state(context);
        break;
    case STATUS_QUERY_BOX_CHARGE_STATE:
        packet.response_code = 0x0ef5;
        packet.value = get_glassbox_charge_status();
        break;
    case STATUS_QUERY_BOX_CHARGE_PERCENT:
        packet.response_code = 0x0ff5;
        packet.value = get_glassbox_charge_percent();
        break;
    case STATUS_QUERY_BRIGHTNESS_LEVEL:
        packet.response_code = 0x12f5;
        packet.value = status_context_byte(
            context, STATUS_BRIGHTNESS_LEVEL_OFFSET);
        break;
    default:
        packet.response_code = (uint16_t)(0x00f5u |
                                          ((uint16_t)selector << 8));
        break;
    }

publish:
    status_context_sink(context)(&packet, 21);
    return 0;
}
