#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027470 @ 0x01027470
 * public-name: controller_handle_slot_find
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_find              <= FUN_01027470 @ 0x01027470
 */
/* net-core controller_handle_slot_find @ 0x01027470.
 * Raw backmap: FUN_01027470@0x01027470. */
#include <stdint.h>

extern uint32_t FUN_0102741e(uint32_t, uint32_t, uint32_t);

uint32_t controller_handle_slot_find(uint32_t object, uint16_t value)
{
    volatile uint8_t *base;
    uint32_t slot;

    if (object == 0) {
        return 0xff;
    }
    base = (volatile uint8_t *)(uintptr_t)object;
    slot = value % base[2];
    if (value == *(volatile uint16_t *)(base + 10u + slot * 2u)) {
        return slot;
    }
    if (base[3] == 0) {
        return FUN_0102741e(object, value, slot);
    }
    return 0xff;
}
