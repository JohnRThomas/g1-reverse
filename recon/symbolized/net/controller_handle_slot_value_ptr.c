#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010274ea @ 0x010274ea
 * public-name: controller_handle_slot_value_ptr
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_value_ptr         <= FUN_010274ea @ 0x010274ea
 */
/* net-core controller_handle_slot_value_ptr @ 0x010274ea.
 * Raw backmap: FUN_010274ea@0x010274ea. */
#include <stdint.h>

extern uint32_t FUN_010274d0(uint32_t);

uint32_t controller_handle_slot_value_ptr(uint32_t object, uint32_t selector)
{
    volatile uint8_t *base = (volatile uint8_t *)(uintptr_t)object;
    uint32_t offset = FUN_010274d0(base[2]);
    uint32_t width = *(volatile uint16_t *)base;
    uint32_t slot = selector & 0xffu;

    return object + offset + width * slot;
}
