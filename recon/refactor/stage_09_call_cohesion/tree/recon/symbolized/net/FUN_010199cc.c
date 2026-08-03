#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010199cc @ 0x010199cc
 * public-name: FUN_010199cc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 */
/* net-core FUN_010199cc @ 0x010199cc */
#include <stdint.h>

extern uint32_t FUN_0100a5a0(void);
extern void sdc_buffer_descriptor_resolve(uint32_t controller, uint32_t *handle,
                         uint16_t *auxiliary);
extern uint8_t *sdc_buffer_payload_get(uint32_t handle);
#define sdc_buffer_descriptor_resolve sdc_buffer_descriptor_resolve
#define sdc_buffer_payload_get sdc_buffer_payload_get

int FUN_010199cc(void)
{
    uint32_t handle;
    uint16_t auxiliary;
    uint32_t controller = FUN_0100a5a0();

    sdc_buffer_descriptor_resolve(controller, &handle, &auxiliary);
    return sdc_buffer_payload_get(handle)[0x13] != 0xffu;
}
