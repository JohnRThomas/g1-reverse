/* CPUNET private byte-state reset @ 0x01012694.
 * Raw back-map: FUN_01012694@0x01012694; extent 0x12. */
#include <stdint.h>

void FUN_01012694(uint8_t *state, uint8_t value)
{
    *(uint16_t *)(state + 0x40) = 0;
    if (*(uint16_t *)(state + 2) == 0x1d)
        value = 0;
    state[0x0d] = value;
}
