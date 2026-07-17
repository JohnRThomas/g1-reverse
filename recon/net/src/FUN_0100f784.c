/* net-core FUN_0100f784 @ 0x100f784  (CFG-directed candidate) */
/* Role: reset controller timing counters. Back-map: FUN_0100f784. */
#include <stdint.h>
void FUN_0100f784(void *owner)
{
    uint8_t *state = *(uint8_t **)((uint8_t *)owner + 4);
    state[0xc5] = 0;
    state[0x100] = 0;
    *(uint16_t *)(state + 0xfc) = 0;
}
