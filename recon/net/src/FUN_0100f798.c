/* net-core FUN_0100f798 @ 0x100f798  (CFG-directed candidate) */
/* Role: clear a controller halfword and advance its generation byte. Back-map: FUN_0100f798. */
#include <stdint.h>
void FUN_0100f798(void *owner)
{
    uint8_t *state = *(uint8_t **)((uint8_t *)owner + 4);
    *(uint16_t *)(state + 0x102) = 0;
    state[0x104] = (uint8_t)(state[0x104] + 1u);
}
