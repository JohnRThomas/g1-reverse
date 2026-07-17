/* net-core FUN_01009d64 @ 0x1009d64 */
#include <stdint.h>

extern uint32_t FUN_01027470(void *, uint16_t);
extern uint32_t FUN_010274ea(void *, uint8_t);
typedef void (*slot_callback_fn)(uint16_t, uint32_t);

uint32_t FUN_01009d64(uint32_t raw_id, uint32_t raw_bank)
{
    uint16_t id = (uint16_t)((uint32_t)raw_id & 0xffffu);
    uint8_t bank = (uint8_t)((uint32_t)raw_bank & 0xffu);
    void *object = ((void *volatile *)0x21000b7cu)[bank];
    uint8_t slot = (uint8_t)FUN_01027470(object, id);

    if (slot == 0xffu) {
        return 3;
    }

    uint8_t *bytes = (uint8_t *)object;
    uintptr_t callback_address =
        ((uintptr_t)*(uint16_t *)(bytes + 6) << 16) |
        (uintptr_t)*(uint16_t *)(bytes + 8);
    uint32_t value = FUN_010274ea(object, slot);
    ((slot_callback_fn)callback_address)(id, value);
    *(uint16_t *)(bytes + 10u + (uint32_t)slot * 2u) = 0xfff0u;
    return 0;
}
