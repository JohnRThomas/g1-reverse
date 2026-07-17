/* readable reconstruction; identity: FUN_0101dec4 @ 0x0101dec4
 * public-name: schedule_node_list_is_locked
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   schedule_node_list_is_locked             <= FUN_0101dec4 @ 0x0101dec4
 * address symbols (name @ address):
 *   g_21001140                               @ 0x21001140
 */
/* net-core FUN_0101dec4 @ 0x0101dec4 */
#include <stdint.h>
uint32_t schedule_node_list_is_locked(void){return *(volatile uint8_t*)0x21001140u;}
