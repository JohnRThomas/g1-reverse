#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01028134 @ 0x01028134
 * public-name: FUN_01028134
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01028134 @ 0x01028134, exact executable extent 0x122. */
/*
 * Retained private-controller reconstruction.
 * Raw entry/backmap: FUN_01028134 @ 0x01028134, exact extent 0x122.
 */
#include <stdint.h>

struct controller_slot_cursor {
    uintptr_t value;
    uint16_t slot_value;
    uint8_t family;
    uint8_t next_slot;
};

extern uint32_t FUN_01009dd8(struct controller_slot_cursor *cursor);
extern uint32_t FUN_01028112(uint32_t candidate, uint32_t active,
                            uint32_t allow_one_bit_difference);

#define controller_access_address_conflicts FUN_01028134

uint32_t controller_access_address_conflicts(
    uint32_t candidate, uint32_t allow_one_bit_difference,
    uint32_t unused)
{
    (void)unused;

    struct controller_slot_cursor cursor;
    uint32_t conflicts;

#define CHECK_FAMILY(family_id, member_offset) do {                         \
        cursor = (struct controller_slot_cursor){ 0u, 0u, family_id, 0u };  \
        while (FUN_01009dd8(&cursor) == 0u) {                               \
            uint32_t active = *(const volatile uint32_t *)                  \
                (cursor.value + member_offset);                             \
            conflicts = FUN_01028112(candidate, active,                     \
                                      allow_one_bit_difference);            \
            if (conflicts != 0u) {                                          \
                return conflicts;                                           \
            }                                                               \
        }                                                                   \
    } while (0)

    CHECK_FAMILY(0u, 0x18u);
    CHECK_FAMILY(1u, 0x18u);
    CHECK_FAMILY(3u, 0u);
    CHECK_FAMILY(4u, 0u);
    CHECK_FAMILY(8u, 0x188u);
    CHECK_FAMILY(10u, 0xe8u);
    CHECK_FAMILY(9u, 0x114u);
#undef CHECK_FAMILY
    return 0u;
}
