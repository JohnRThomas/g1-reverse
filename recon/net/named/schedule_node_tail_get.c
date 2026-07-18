/* readable reconstruction; identity: FUN_0101dda8 @ 0x0101dda8
 * public-name: schedule_node_tail_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   schedule_node_tail_get                   <= FUN_0101dda8 @ 0x0101dda8
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101dda8 @ 0x0101dda8
 * Readable identity: schedule_node_tail_get.
 */
#include <stdint.h>

uint32_t schedule_node_tail_get(void)
{
    uint32_t node = *(volatile uint32_t *)0x2100113cu;

    while (node != 0u) {
        uint32_t next = *(volatile uint32_t *)(uintptr_t)(node + 0x18u);
        if (next == 0u) {
            return node;
        }
        node = next;
    }
    return 0u;
}
