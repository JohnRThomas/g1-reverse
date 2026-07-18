/* FUN_01019eb4 @ 0x01019eb4: inspect the resolved controller buffer mode. */
#include <stdint.h>

extern uint32_t FUN_0100a5a0(void);
extern void FUN_0102714a(uint32_t descriptor, uint32_t *handle, uint16_t *auxiliary);
extern uint8_t *FUN_010270d2(uint32_t handle);
#define sdc_buffer_descriptor_resolve FUN_0102714a
#define sdc_buffer_payload_get FUN_010270d2

__attribute__((optimize("O2")))
uint32_t sdc_buffer_mode_matches(const uint16_t *flags, uint32_t mode)
{
    struct {
        uint16_t reserved;
        uint16_t auxiliary;
        uint32_t handle;
    } locals;
    uint32_t descriptor = FUN_0100a5a0();
    sdc_buffer_descriptor_resolve(descriptor, &locals.handle, &locals.auxiliary);
    uint8_t *payload = sdc_buffer_payload_get(locals.handle);
    if (mode == 0u) {
        return ((*flags & 0x10ffu) == 0u);
    }
    if (mode == 3u) {
        return (payload[0x1c] >> 3) & 1u;
    }
    return 0u;
}

/* Raw identity/back-map: FUN_01019eb4 @ 0x01019eb4, true extent 0x44. */
extern __typeof(sdc_buffer_mode_matches) FUN_01019eb4
    __attribute__((alias("sdc_buffer_mode_matches")));
