#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a954 @ 0x0100a954
 * public-name: FUN_0100a954
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ctrl_pending_req_target_id         @ 0x21000c30
 */
/* net-core FUN_0100a954 @ 0x0100a954 */
#include <stdint.h>
void FUN_0100a954(uint16_t value){*(volatile uint16_t *)((unsigned long)&g_net_ctrl_pending_req_target_id) /*=0x21000c30*/=value;}
