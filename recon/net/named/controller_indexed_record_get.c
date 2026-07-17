/* readable reconstruction; identity: FUN_0100ca80 @ 0x0100ca80
 * public-name: controller_indexed_record_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_indexed_record_get            <= FUN_0100ca80 @ 0x0100ca80
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core controller_indexed_record_get @ 0x0100ca80.
 * Raw/address backmap: FUN_0100ca80@0x0100ca80. */
#include <stddef.h>
#include <stdint.h>
#define controller_indexed_record_get controller_indexed_record_get

void *controller_indexed_record_get(uint32_t index)
{
    volatile const uint8_t * const controller_state =
        (volatile const uint8_t *)0x21000d18u;

    if (index >= controller_state[1]) {
        return NULL;
    }
    return (void *)(0x21000d18u + 2u + index * 16u);
}
