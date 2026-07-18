/* FUN_01019ef8 @ 0x01019ef8: match metadata in the resolved controller buffer. */
#include <stdint.h>

extern uint32_t FUN_0100a5a0(void);
extern void FUN_0102714a(uint32_t descriptor, uint32_t *handle, uint16_t *auxiliary);
extern uint8_t *FUN_010270d2(uint32_t handle);
#define sdc_buffer_descriptor_resolve FUN_0102714a
#define sdc_buffer_payload_get FUN_010270d2

__attribute__((optimize("O2")))
uint32_t sdc_buffer_metadata_matches(uint32_t expected_kind, uint32_t expected_value)
{
    struct {
        uint16_t reserved;
        uint16_t auxiliary;
        uint32_t handle;
    } locals;
    uint32_t descriptor = FUN_0100a5a0();
    sdc_buffer_descriptor_resolve(descriptor, &locals.handle, &locals.auxiliary);
    const uint8_t *payload = sdc_buffer_payload_get(locals.handle);
    uint16_t value = (uint16_t)payload[0x21] | ((uint16_t)payload[0x22] << 8);
    return payload[0x20] == expected_kind && value == expected_value;
}

/* Raw identity/back-map: FUN_01019ef8 @ 0x01019ef8, true extent 0x3a. */
extern __typeof(sdc_buffer_metadata_matches) FUN_01019ef8
    __attribute__((alias("sdc_buffer_metadata_matches")));
