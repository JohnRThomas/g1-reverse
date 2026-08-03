#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01019eb4 @ 0x01019eb4
 * public-name: FUN_01019eb4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 */
/* FUN_01019eb4 @ 0x01019eb4: inspect the resolved controller buffer mode. */
#include <stdint.h>

extern uint32_t FUN_0100a5a0(void);
extern void sdc_buffer_descriptor_resolve(uint32_t descriptor, uint32_t *handle, uint16_t *auxiliary);
extern uint8_t *sdc_buffer_payload_get(uint32_t handle);
#define sdc_buffer_descriptor_resolve sdc_buffer_descriptor_resolve
#define sdc_buffer_payload_get sdc_buffer_payload_get

__attribute__((optimize("O2")))
uint32_t FUN_01019eb4(const uint16_t *flags, uint32_t mode)
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
