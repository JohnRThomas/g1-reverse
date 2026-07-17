/* readable reconstruction; identity: FUN_0100ca68 @ 0x0100ca68
 * public-name: sdc_llcp_procedure_slot_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_procedure_slot_get              <= FUN_0100ca68 @ 0x0100ca68
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100ca68 @ 0x100ca68  (CFG-directed candidate) */
#include <stdint.h>

/* Raw back-map: FUN_0100ca68 @ 0x0100ca68, exact extent 0x14 bytes. */
void *sdc_llcp_procedure_slot_get(uint32_t index)
{
    volatile const uint8_t *const table_state =
        (volatile const uint8_t *)0x21000d18u;

    if (index >= table_state[1]) {
        return 0;
    }
    return (void *)(uintptr_t)(0x21000d18u + 0x82u + index * 0x10u);
}
