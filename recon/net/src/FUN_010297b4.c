/* net-core FUN_010297b4 @ 0x10297b4  (CFG-directed candidate) */
/* CPUNET 0x010297b4, true executable extent 0xce. Raw backmap: FUN_010297b4. */
#include <stdint.h>

extern uint32_t FUN_0100e8b0(uint32_t descriptor);
extern uint32_t FUN_0100e8b8(uint32_t descriptor);
extern uint16_t FUN_0100e8c4(uint32_t descriptor);
extern uint32_t FUN_0101f8d8(void);
extern uint32_t FUN_01028486(uint32_t mode);
extern uint32_t FUN_0102971e(uint32_t mask);

uint32_t FUN_010297b4(uint8_t *state, uint32_t descriptor, uint8_t *changes)
{
    uint32_t requested = FUN_0100e8b0(descriptor);
    uint32_t secondary = FUN_0100e8b8(descriptor);
    uint32_t old_primary = FUN_0102971e(secondary);
    uint32_t old_secondary = FUN_0102971e(requested);
    uint32_t changed = ((old_primary | old_secondary) & 0xffu) != 0u;

    if ((FUN_0101f8d8() & secondary & 0xffu) == 0u) {
        old_primary = 0u;
    }
    if ((FUN_0101f8d8() & requested & 0xffu) == 0u) {
        old_secondary = 0u;
    }
    changes[0] = state[0x6e] == old_primary ? 0u : (uint8_t)old_primary;
    changes[1] = state[0x6f] == old_secondary ? 0u : (uint8_t)old_secondary;
    if ((changes[0] == 0u) && (changes[1] == 0u) &&
        ((uint16_t)(FUN_0100e8c4(descriptor) +
                    (uint16_t)~*(uint16_t *)(state + 0xbc)) > 0x7ffdu)) {
        changed = 0u;
    }
    if ((old_primary != 0u ? old_primary == 8u :
         FUN_01028486(state[0x6e]) == 3u) && state[0x16c] == 1u) {
        if (*(uint16_t *)(state + 0x170) == 1u) {
            if (state[0x6e] != 4u) {
                changes[0] = 4u;
            } else {
                changes[0] = 8u;
            }
        } else if (state[0x6e] != 8u) {
            changes[0] = 8u;
        }
    }
    return changed;
}
