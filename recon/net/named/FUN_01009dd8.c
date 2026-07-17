/* readable reconstruction; identity: FUN_01009dd8 @ 0x01009dd8
 * public-name: FUN_01009dd8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_value_ptr         <= FUN_010274ea @ 0x010274ea
 */
/* net-core FUN_01009dd8 @ 0x01009dd8, exact Thumb extent 0x80 bytes. */
#include <stdint.h>

extern uint32_t controller_handle_slot_value_ptr(const void *descriptor, uint32_t slot);
/* Back-map: FUN_010274ea @ 0x010274ea = controller_handle_slot_value_ptr. */

/* The firmware's descriptor-family pointer table. */
#define DESCRIPTOR_FAMILY_TABLE ((const volatile uintptr_t *)0x21000b7cu)

struct controller_slot_cursor {
    uint32_t value;
    uint16_t slot_value;
    uint8_t family;
    uint8_t next_slot;
};

uint32_t FUN_01009dd8(struct controller_slot_cursor *cursor)
{
    const volatile uint8_t *descriptor =
        (const volatile uint8_t *)DESCRIPTOR_FAMILY_TABLE[cursor->family];

    if (descriptor == 0) {
        return 2u;
    }

    while (cursor->next_slot < descriptor[2]) {
        uint8_t slot = cursor->next_slot++;
        uint16_t value = *(const volatile uint16_t *)(descriptor +
            ((uint32_t)(slot + 4u) * 2u) + 2u);
        if (value == 0xfff0u) {
            continue;
        }
        cursor->slot_value = value;
        cursor->value = controller_handle_slot_value_ptr((const void *)descriptor, slot);
        return 0u;
    }
    return 2u;
}
