#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005bd18 @ 0x0005bd18
 * public-name: gatt_parse_read_by_type_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_parse_read_by_type_rsp              <= FUN_0005bd18 @ 0x0005bd18
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   gatt_req_send                            <= FUN_00082aee @ 0x00082aee
 *   gatt_discover_next                       <= FUN_00082d2e @ 0x00082d2e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_gatt_parse_read_by_type_rsp_128_THUMB @ 0x0005c005
 *   ADDR_read_included_uuid_encode_THUMB     @ 0x0008275f
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4ca8                             @ 0x000f4ca8
 */
/* Reconstructed FUN_0005bd18 @ 0x5bd18 */
#include <stdint.h>

extern int  bt_uuid_cmp(void *packet);
extern void log_msg_create_3arg(uint32_t module, uint32_t event, void *detail);
extern int  gatt_req_send(uint32_t, uint32_t, void *, uint32_t,
                         uint32_t, uint32_t);
extern void gatt_discover_next(uint32_t context, uint32_t last_id, void *consumer);
extern void memset_bytes(void *destination, int value, uint32_t size);

typedef int (*record_consumer_t)(uint32_t, void *, void *);

struct decoded_value {
    uint8_t *payload;
    uint16_t field_a;
    uint16_t field_b;
    uint8_t bytes[17];
};

struct output_record {
    const void *attribute;
    uint8_t cleared[8];
    const void *value;
    uint16_t id;
    uint16_t padding;
};

static __attribute__((always_inline)) inline int
emit_record(uint32_t context, int *consumer, const void *attribute,
            const void *value, uint16_t id)
{
    struct output_record output;
    output.attribute = attribute;
    memset_bytes(output.cleared, 0, 0x10);
    output.value = value;
    output.id = id;
    return ((record_consumer_t)(uintptr_t)consumer[1])
           (context, &output, consumer);
}

void gatt_parse_read_by_type_rsp(uint32_t context, int status, const uint8_t *data,
                  int length, int *consumer)
{
    record_consumer_t consume = (record_consumer_t)(uintptr_t)consumer[1];
    uint32_t remaining;
    uint32_t stride;
    uint16_t last_id = 0;
    const uint8_t *record;
    int consumer_kind;

    if (status != 0)
        goto malformed;

    consumer_kind = (int8_t)consumer[4];
    if (consumer_kind == 2) {
        struct decoded_value value;
        uint8_t query[4] = { 0, 0, 0x02, 0x28 };

        stride = data[0];
        if (stride == 6)
            value.bytes[0] = 2;
        else if (stride == 8)
            value.bytes[0] = 0;
        else {
            struct { uint32_t type, message, value; } detail =
                { 3, UINT32_C(0x000f4ca8), stride };
            log_msg_create_3arg(UINT32_C(0x00088128), 0x1840, &detail);
            goto malformed;
        }

        remaining = (uint32_t)(length - 1) & 0xffffu;
        record = data + 1;
        while (stride <= remaining) {
            last_id = *(const uint16_t *)record;
            if (last_id == 0)
                goto malformed;
            value.field_a = *(const uint16_t *)(record + 2);
            value.field_b = *(const uint16_t *)(record + 4);

            if (value.bytes[0] == 0) {
                value.payload = value.bytes;
                *(uint16_t *)(value.bytes + 2) =
                    *(const uint16_t *)(record + 6);
            } else {
                *(uint16_t *)((uint8_t *)consumer + 10) = value.field_a;
                *(uint16_t *)((uint8_t *)consumer + 12) = value.field_b;
                *(uint16_t *)((uint8_t *)consumer + 8) = last_id;
                if (gatt_req_send(context, UINT32_C(0x0005c005), consumer,
                                 UINT32_C(0x0008275f), 10, 2) == 0)
                    return;
                gatt_discover_next(context, last_id, consumer);
                return;
            }

            if (consumer[0] == 0 || bt_uuid_cmp(value.bytes) == 0) {
                if (emit_record(context, consumer, query, &value, last_id) == 0)
                    return;
            }
            remaining = (remaining - stride) & 0xffffu;
            record += stride;
        }
        goto completed;
    }

    if (consumer_kind == 3) {
        struct decoded_value value;
        uint8_t query[4] = { 0, 0, 0x03, 0x28 };

        stride = data[0];
        if (stride == 7)
            value.bytes[0] = 0;
        else if (stride == 0x15)
            value.bytes[0] = 2;
        else {
            struct { uint32_t type, message, value; } detail =
                { 3, UINT32_C(0x000f4ca8), stride };
            log_msg_create_3arg(UINT32_C(0x00088128), 0x1840, &detail);
            goto malformed;
        }

        remaining = (uint32_t)(length - 1) & 0xffffu;
        record = data + 1;
        while (stride <= remaining) {
            unsigned i;
            last_id = *(const uint16_t *)record;
            if (last_id == 0)
                goto malformed;
            if (value.bytes[0] == 0) {
                *(uint16_t *)(value.bytes + 2) =
                    *(const uint16_t *)(record + 5);
            } else {
                for (i = 0; i != 16; ++i)
                    value.bytes[i + 1] = record[i + 5];
            }

            if (consumer[0] == 0 || bt_uuid_cmp(value.bytes) == 0) {
                value.field_a = *(const uint16_t *)(record + 3);
                value.field_b = (uint8_t)record[2];
                value.payload = value.bytes;
                if (emit_record(context, consumer, query, &value, last_id) == 0)
                    return;
            }
            remaining = (remaining - stride) & 0xffffu;
            record += stride;
        }
        goto completed;
    }

    {
        uint8_t packet[9];
        const uint8_t *attribute = (const uint8_t *)(uintptr_t)consumer[0];
        uint32_t format;

        if (attribute[0] != 0)
            goto malformed;
        format = *(const uint16_t *)(attribute + 2) - 0x2900u;
        stride = data[0];
        remaining = (uint32_t)(length - 1) & 0xffffu;
        record = data + 1;

        while (stride <= remaining) {
            last_id = *(const uint16_t *)record;
            if (last_id == 0)
                goto malformed;
            switch (format) {
            case 0:
            case 2:
            case 3:
                packet[0] = record[2];
                packet[1] = record[3];
                break;
            case 4:
                packet[0] = record[2];
                packet[1] = record[3];
                packet[2] = record[4];
                packet[3] = record[5];
                packet[4] = record[6];
                packet[5] = record[7];
                packet[6] = record[8];
                break;
            default:
                goto malformed;
            }

            if (emit_record(context, consumer, attribute, packet, last_id) == 0)
                return;
            remaining = (remaining - stride) & 0xffffu;
            record += stride;
        }
    }

completed:
    if (remaining == 0 && last_id != 0) {
        gatt_discover_next(context, last_id, consumer);
        return;
    }
malformed:
    consume(context, 0, consumer);
}
