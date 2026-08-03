#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01009d64 @ 0x01009d64
 * public-name: FUN_01009d64
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_find              <= FUN_01027470 @ 0x01027470
 *   controller_handle_slot_value_ptr         <= FUN_010274ea @ 0x010274ea
 */
/* net-core FUN_01009d64 @ 0x1009d64 */
#include <stdint.h>

extern uint32_t controller_handle_slot_find(void *, uint16_t);
extern uint32_t controller_handle_slot_value_ptr(void *, uint8_t);
typedef void (*slot_callback_fn)(uint16_t, uint32_t);

uint32_t FUN_01009d64(uint32_t raw_id, uint32_t raw_bank)
{
    uint16_t id = (uint16_t)((uint32_t)raw_id & 0xffffu);
    uint8_t bank = (uint8_t)((uint32_t)raw_bank & 0xffu);
    void *object = ((void *volatile *)G1N_21000b7c)[bank];
    uint8_t slot = (uint8_t)controller_handle_slot_find(object, id);

    if (slot == 0xffu) {
        return 3;
    }

    uint8_t *bytes = (uint8_t *)object;
    uintptr_t callback_address =
        ((uintptr_t)*(uint16_t *)(bytes + 6) << 16) |
        (uintptr_t)*(uint16_t *)(bytes + 8);
    uint32_t value = controller_handle_slot_value_ptr(object, slot);
    ((slot_callback_fn)callback_address)(id, value);
    *(uint16_t *)(bytes + 10u + (uint32_t)slot * 2u) = 0xfff0u;
    return 0;
}
