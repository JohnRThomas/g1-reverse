#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101dc50 @ 0x0101dc50
 * public-name: controller_packet_space_limit
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_space_limit            <= FUN_0101dc50 @ 0x0101dc50
 */
/* net-core FUN_0101dc50 @ 0x101dc50  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_0100d3c0(void *, uint32_t, uint32_t, uint32_t, uint32_t);
static uint16_t clamp_nonnegative_u16(uint32_t value)
{
    return (uint16_t)(value & ~((uint32_t)((int32_t)value >> 31)));
}
/* Readable role: controller_packet_space_limit. Raw back-map: FUN_0101dc50 @ 0x0101dc50. */
uint32_t controller_packet_space_limit(void *state_pointer, uint32_t unused1, uint32_t unused2,
                      uint32_t call_context)
{
    uint8_t *state = (uint8_t *)state_pointer;
    uint32_t available;
    uint32_t physical;
    (void)unused1;
    (void)unused2;
    if (state[0xc9] == 0)
        available = 2u - *(uint16_t *)(state + 0xf6);
    else
        available = (uint32_t)*(uint16_t *)(state + 0xf8) -
                    (uint32_t)*(uint16_t *)(state + 0xf6) - 4u;
    if (state[0xf4] != 0 &&
        FUN_0100d3c0(state + 0xa8, 9u, state[0xc5], 0u, call_context) == 0u)
        return 0u;
    if (state[0xcb] == 0 &&
        FUN_0100d3c0(state + 0xa8, 6u, state[0xc5], 0u, call_context) == 0u)
        return clamp_nonnegative_u16(available);
    physical = (*(uint32_t *)(state + 0xec) - 4u) - *(uint32_t *)(state + 0xe8);
    if ((int32_t)physical <= (int32_t)available)
        available = physical;
    return clamp_nonnegative_u16(available);
}
