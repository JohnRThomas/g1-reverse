/* net-core FUN_0100aeac @ 0x0100aeac, exact Thumb extent 0x60 bytes. */
#include <stdint.h>

#define CONNECTION_STATE ((volatile uint8_t *)0x21000c48u)

uint32_t FUN_0100aeac(uint32_t requested_side)
{
    uint8_t active_side = CONNECTION_STATE[0x24];
    if ((active_side == 0u && requested_side != 1u) ||
        (active_side != 0u && requested_side != 0u)) {
        return 0u;
    }

    uint32_t ready;
    if ((CONNECTION_STATE[0xb4] & 0x10u) != 0u) {
        if (active_side == 0u) {
            goto check_nonzero_state;
        }
        ready = 0u;
    } else {
        const volatile uint8_t *flags =
            *(const volatile uint8_t * const volatile *)(CONNECTION_STATE + 0xb8);
        ready = ((flags[0] & 0x10u) == 0u);
        if (*(const volatile uint32_t *)(CONNECTION_STATE + 0x38) == 0u &&
            *(const volatile int16_t *)(CONNECTION_STATE + 0xbc) != 0) {
            return 1u;
        }
        if (active_side == 0u) {
            if (ready != 0u) {
                return 1u;
            }
            goto check_nonzero_state;
        }
    }

    if ((*(const volatile uint16_t *)(CONNECTION_STATE + 0x32) & 2u) != 0u) {
        const volatile uint8_t *entry =
            *(const volatile uint8_t * const volatile *)(CONNECTION_STATE + 0x7c);
        return entry[3] == 2u ? 0u : 1u;
    }
    if (ready != 0u) {
        return 1u;
    }

check_nonzero_state:
    return *(const volatile uint16_t *)(CONNECTION_STATE + 0x32) != 0u;
}
