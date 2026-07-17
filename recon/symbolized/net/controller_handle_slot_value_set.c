#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102751a @ 0x0102751a
 * public-name: controller_handle_slot_value_set
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_value_set         <= FUN_0102751a @ 0x0102751a
 */
/* net-core FUN_0102751a @ 0x102751a  (CFG-directed candidate) */

#include <stdint.h>
extern uintptr_t controller_handle_slot_value_ptr(void *, uint32_t); /* FUN_010274ea @ 0x010274ea. */
/* Readable role: controller_handle_slot_value_set. Raw back-map: FUN_0102751a @ 0x0102751a. */
uintptr_t controller_handle_slot_value_set(void *descriptor, uint32_t raw_value, uint32_t raw_slot)
{
    uint8_t slot = (uint8_t)raw_slot;
    *(uint16_t *)((uint8_t *)descriptor + ((uint32_t)(slot + 4u) * 2u) + 2u) =
        (uint16_t)raw_value;
    return controller_handle_slot_value_ptr(descriptor, slot);
}
