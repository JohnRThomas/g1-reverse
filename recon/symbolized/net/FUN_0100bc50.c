#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100bc50 @ 0x0100bc50
 * public-name: FUN_0100bc50
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100bc50 @ 0x100bc50  (parity 300 trials PROVEN) */

unsigned char FUN_0100bc50(void) {
    return *(volatile unsigned char *)(((unsigned long)&g_net_radio_addr_match_tbl) /*=0x21000d18*/ + 0x18b);
}
