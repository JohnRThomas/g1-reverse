#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102609e @ 0x0102609e
 * public-name: FUN_0102609e
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET extended LE advertising report encoder @ 0x0102609e.
 * Raw back-map: FUN_0102609e@0x0102609e; true executable extent 0x84.
 * The archive-family attribution is provenance only: this private SDC body is
 * retained as readable C and is not replaced by an archive member.
 */
#include <stdint.h>

extern void FUN_01025998(void *destination, const void *source,
                         uint32_t length);

void FUN_0102609e(volatile uint8_t *event,
                                    const volatile uint8_t *record)
{
    uint16_t event_type_and_address_type =
        *(const volatile uint16_t *)(record + 4);
    uint8_t header = event[1];

    event[0] = (uint8_t)event_type_and_address_type;
    event[1] = header & 0xf0u;
    uint8_t event_type = (uint8_t)((event_type_and_address_type >> 8) & 0x0fu);
    event[1] = (uint8_t)((header & 0xf0u) | event_type);

    uint16_t payload_length = *(const volatile uint16_t *)(record + 6);
    event[2] = (uint8_t)payload_length;
    uint8_t tail = event[3];
    event[3] = tail & 0xc0u;
    event[1] = (uint8_t)((header & 0xc0u) | event_type);
    uint8_t length_high = (uint8_t)((payload_length >> 8) & 0x3fu);
    event[3] = (uint8_t)((tail & 0xc0u) | length_high);

    uint8_t address_type = (uint8_t)((record[8] & 3u) << 4);
    event[1] = (uint8_t)((header & 0x80u) | event_type | address_type);
    event[3] = length_high;
    event[1] = (uint8_t)((event_type | address_type | (record[9] << 6)) & 0x7fu);

    const volatile uint8_t *payload =
        (const volatile uint8_t *)(uintptr_t)
        *(const volatile uint32_t *)record;
    if (payload != event + 4)
        FUN_01025998((void *)(event + 4), (const void *)payload, payload_length);
}

/* Raw identity/back-map: FUN_0102609e@0x0102609e. */
