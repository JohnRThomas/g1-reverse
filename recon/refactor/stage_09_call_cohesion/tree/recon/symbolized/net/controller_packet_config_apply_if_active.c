#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100cb4c @ 0x0100cb4c
 * public-name: controller_packet_config_apply_if_active
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_config_apply_if_active <= FUN_0100cb4c @ 0x0100cb4c
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core controller_packet_config_apply_if_active @ 0x0100cb4c.
 * Raw backmap: FUN_0100cb4c@0x0100cb4c. */
#include <stdint.h>

extern void FUN_0101fc40(uint32_t, uint32_t, uint32_t);

uint32_t controller_packet_config_apply_if_active(uint32_t packet_value)
{
    volatile uint8_t *controller_state =
        (volatile uint8_t *)((unsigned long)&g_net_radio_addr_match_tbl) /*=0x21000d18*/;
    uint32_t active = controller_state[0x18a];

    if (active != 0) {
        uint32_t count = controller_state[1];
        if (count != 0) {
            FUN_0101fc40(G1N_21000d1a, count, packet_value);
        } else {
            active = 0;
        }
    }
    return active;
}
