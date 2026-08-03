#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100c738 @ 0x0100c738
 * public-name: FUN_0100c738
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100c738 @ 0x100c738  (parity 300 trials PROVEN) */

unsigned short FUN_0100c738(void) {
    return *(volatile unsigned short *)(((unsigned long)&g_net_radio_addr_match_tbl) /*=0x21000d18*/ + 0x18c);
}
