#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01020820 @ 0x01020820
 * public-name: FUN_01020820
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01020820 @ 0x1020820  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_01021654(uint16_t, uint8_t, uint8_t, uint32_t);
extern uint32_t FUN_01021694(uint16_t, uint8_t, uint8_t, uint32_t);
void FUN_01020820(uint32_t argument)
{
    volatile uint8_t *state = (volatile uint8_t *)(uintptr_t)0x210015f0u;
    uint32_t result;
    state[0x0c] = 2;
    if (state[0x29] == 1)
        result = FUN_01021654(*(volatile uint16_t *)(state + 0x1c), state[0x28], state[0x18], argument);
    else
        result = FUN_01021694(*(volatile uint16_t *)(state + 0x1c), state[0x28], state[0x18], argument);
    *(volatile uint32_t *)(state + 0x10) = result;
    *(volatile uint32_t *)(uintptr_t)0x4100c144u = 0;
    *(volatile uint32_t *)(uintptr_t)0x4100c544u = *(volatile uint32_t *)(state + 0x24) + result;
}
