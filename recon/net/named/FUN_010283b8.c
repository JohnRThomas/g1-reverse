/* readable reconstruction; identity: FUN_010283b8 @ 0x010283b8
 * public-name: FUN_010283b8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010283b8 @ 0x010283b8, exact executable extent 0x46. */
/*
 * Retained private-controller reconstruction.
 * Raw entry/backmap: FUN_010283b8 @ 0x010283b8, exact extent 0x46.
 */
#include <stdint.h>

struct controller_slot_cursor {
    uintptr_t value;
    uint16_t slot_value;
    uint8_t family;
    uint8_t next_slot;
};

extern uint32_t FUN_010283a4(void);
extern uint32_t FUN_01019088(void);
extern uint32_t FUN_01009dd8(struct controller_slot_cursor *cursor);
extern uint8_t FUN_010141d4(uintptr_t item);
extern uint8_t FUN_01012330(uintptr_t item);

#define controller_group2_activity_busy FUN_010283b8

uint32_t controller_group2_activity_busy(uint32_t unused0, uint32_t unused1)
{
    (void)unused0;
    (void)unused1;

    if (FUN_010283a4() != 0u && FUN_01019088() != 0u) {
        return 1u;
    }

    struct controller_slot_cursor cursor = { 0u, 0u, 2u, 0u };
    while (FUN_01009dd8(&cursor) == 0u) {
        if (FUN_010141d4(cursor.value) != 0u &&
            FUN_01012330(cursor.value) != 0u) {
            return 1u;
        }
    }
    return 0u;
}
