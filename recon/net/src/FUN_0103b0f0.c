/* net-core FUN_0103b0f0 @ 0x0103b0f0 */
#include <stdint.h>

uint32_t FUN_0103b0f0(uint32_t object)
{
    const uint8_t *state;
    uint32_t active;

    if (object == 0u) {
        return 0u;
    }
    state = *(const uint8_t **)(uintptr_t)(object + 0xcu);
    active = state[1] & 1u;
    if (active != 0u) {
        active = state[0] == 0u;
    }
    return active;
}
