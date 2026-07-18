#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101d890 @ 0x0101d890
 * public-name: FUN_0101d890
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_radio_idle_state_finish       <= FUN_0100b594 @ 0x0100b594
 */
/* net-core FUN_0101d890 @ 0x0101d890
 * Catalog-missed executable ownership is [0x0101d890, 0x0101d8e2).
 * Raw backmap: FUN_0101d890@0x0101d890. */
#include <stdint.h>

extern void controller_radio_idle_state_finish(uint32_t context, uint32_t active_flag);
extern void FUN_0101c6d0(uint32_t context, uint32_t event);

#define controller_radio_idle_state_finish controller_radio_idle_state_finish
#define CONTROLLER_STATE_OWNER_ADDR 0x21001128u

void FUN_0101d890(uint32_t context)
{
    volatile uint8_t *state = (volatile uint8_t *)(uintptr_t)
        *(volatile uint32_t *)CONTROLLER_STATE_OWNER_ADDR;

    if (state[0x100u] != 0u &&
        *(volatile uint16_t *)(state + 0xfcu) >=
            *(volatile uint16_t *)(state + 0xfeu)) {
        FUN_0101c6d0(0u, 0u);
        return;
    }

    if ((int8_t)state[0x104u] != 0 &&
        *(volatile uint16_t *)(state + 0x102u) >=
            *(volatile uint16_t *)(state + 0xfeu)) {
        FUN_0101c6d0(0u, 0u);
        return;
    }

    uint16_t pending = *(volatile uint16_t *)(state + 0xf8u);
    if (*(volatile uint16_t *)(state + 0xfau) >= pending) {
        FUN_0101c6d0(0u, 0u);
        return;
    }

    uint32_t active = state[0xc9u];
    uint16_t completed = *(volatile uint16_t *)(state + 0xf6u);
    if ((active != 0u && completed < pending) ||
        (active == 0u && completed <= 5u)) {
        controller_radio_idle_state_finish(context, active);
        return;
    }

    FUN_0101c6d0(0u, 0u);
}
