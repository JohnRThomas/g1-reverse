/* readable reconstruction; identity: FUN_0100bc04 @ 0x0100bc04
 * public-name: controller_indexed_state_byte_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_indexed_state_byte_get        <= FUN_0100bc04 @ 0x0100bc04
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core controller_indexed_state_byte_get @ 0x0100bc04.
 * Raw backmap: FUN_0100bc04@0x0100bc04. */
#include <stdint.h>

uint32_t controller_indexed_state_byte_get(uint32_t index)
{
    volatile uint8_t *controller_state =
        (volatile uint8_t *)0x21000d18u;

    if (index >= controller_state[1]) {
        return 0;
    }
    return controller_state[0x142u + index];
}
