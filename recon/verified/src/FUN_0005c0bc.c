/* Reconstructed FUN_0005c0bc @ 0x5c0bc */
#include <stdint.h>

extern int  FUN_00080d3e(void *packet, ...);
extern void FUN_00082a42(uint32_t module, uint32_t event, void *detail);
extern void FUN_00082d2e(uint32_t context, uint32_t last_id, void *consumer);
extern void FUN_00086c78(void *destination, int value, uint32_t size);

typedef int (*record_consumer_t)(uint32_t context, void *record,
                                 void *consumer);

struct emitted_record {
    uint8_t *packet;
    uint8_t payload[12];
    uint16_t id;
};

void FUN_0005c0bc(uint32_t context, int status, const uint8_t *data,
                  int length, int *consumer)
{
    uint32_t stride;
    uint32_t remaining;
    uint32_t last_id = 0;
    const uint8_t *record;
    uint8_t packet[17];
    int skip_next = 0;
    record_consumer_t consume = (record_consumer_t)(uintptr_t)consumer[1];

    if (status != 0)
        goto malformed;

    if (data[0] == 1) {
        stride = 4;
        packet[0] = 0;
    } else if (data[0] == 2) {
        stride = 0x12;
        packet[0] = 2;
    } else {
        struct {
            uint32_t type;
            uint32_t message;
            uint32_t value;
        } detail = { 3, UINT32_C(0x000f4cbc), data[0] };
        FUN_00082a42(UINT32_C(0x00088128), 0x1840, &detail);
        goto malformed;
    }

    remaining = ((uint32_t)(length - 1) & 0xffffu);
    if (remaining < stride)
        goto malformed;
    remaining /= stride;
    record = data + 1;

    for (;;) {
        int accepted;

        if (remaining == 0) {
            FUN_00082d2e(context, last_id, consumer);
            return;
        }

        last_id = *(const uint16_t *)record;
        if (skip_next) {
            skip_next = 0;
            goto advance;
        }

        if (packet[0] == 0) {
            packet[2] = record[2];
            packet[3] = record[3];
        } else if (packet[0] == 2) {
            unsigned i;
            for (i = 0; i != 16; ++i)
                packet[i + 1] = record[i + 2];
        }

        if (consumer[0] != 0 && FUN_00080d3e(packet) != 0)
            goto advance;

        if ((int8_t)consumer[4] == 4) {
            uint8_t query0[4] = { 0, 0, 0x00, 0x28 };
            uint8_t query1[4] = { 0, 0, 0x01, 0x28 };
            uint8_t query2[4] = { 0, 0, 0x02, 0x28 };

            if (FUN_00080d3e(packet, query0) == 0)
                goto advance;
            if (FUN_00080d3e(packet, query1) == 0)
                goto advance;
            if (FUN_00080d3e(packet, query2) == 0)
                goto advance;
            query2[2] = 0x03;
            if (FUN_00080d3e(packet, query2) == 0) {
                skip_next = 1;
                goto advance;
            }
        }

        {
            struct emitted_record output;
            output.packet = packet;
            FUN_00086c78(output.payload, 0, 0x10);
            output.id = (uint16_t)last_id;
            accepted = consume(context, &output, consumer);
        }
        if (accepted == 0)
            return;

advance:
        --remaining;
        record += stride;
    }

malformed:
    consume(context, 0, consumer);
}
