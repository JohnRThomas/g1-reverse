#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100bbec @ 0x0100bbec
 * public-name: controller_indexed_status_byte_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_indexed_status_byte_get       <= FUN_0100bbec @ 0x0100bbec
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core controller_indexed_status_byte_get @ 0x0100bbec.
 * Raw/address backmap: FUN_0100bbec@0x0100bbec. */
#include <stdint.h>
#define controller_indexed_status_byte_get controller_indexed_status_byte_get

uint32_t controller_indexed_status_byte_get(uint32_t index)
{
    volatile const uint8_t * const controller_state =
        (volatile const uint8_t *)((unsigned long)&g_net_radio_addr_match_tbl) /*=0x21000d18*/;

    if (index >= controller_state[1]) {
        return 0;
    }
    return controller_state[0x14au + index];
}
