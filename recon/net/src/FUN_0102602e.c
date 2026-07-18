/* CPUNET legacy LE advertising report encoder @ 0x0102602e.
 * Raw back-map: FUN_0102602e@0x0102602e; true executable extent 0x70.
 * The archive-family attribution is provenance only: this private SDC body is
 * retained as readable C and is not replaced by an archive member.
 */
#include <stdint.h>

extern void FUN_01025998(void *destination, const void *source,
                         uint32_t length);

uint8_t sdc_legacy_adv_report_encode(volatile uint8_t *event,
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
    event[1] = (uint8_t)((header & 0xc0u) | event_type);
    event[3] = (uint8_t)(payload_length >> 8);

    uint8_t address_type = (uint8_t)((record[8] & 3u) << 4);
    event[1] = (uint8_t)(event_type | address_type);
    event[1] = (uint8_t)(event_type | address_type | (record[9] << 6));

    const volatile uint8_t *payload =
        (const volatile uint8_t *)(uintptr_t)
        *(const volatile uint32_t *)record;
    if (payload != event + 4) {
        uint16_t copy_length = payload_length;
        if (copy_length > 0xfau)
            copy_length = 0xfbu;
        FUN_01025998((void *)(event + 4), (const void *)payload, copy_length);
    }

    return (uint8_t)(payload_length + 4u);
}

/* Raw identity/back-map: FUN_0102602e@0x0102602e. */
extern __typeof(sdc_legacy_adv_report_encode) FUN_0102602e
    __attribute__((alias("sdc_legacy_adv_report_encode")));
