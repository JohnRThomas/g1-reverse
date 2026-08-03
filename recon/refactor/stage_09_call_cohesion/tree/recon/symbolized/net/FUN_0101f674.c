#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f674 @ 0x0101f674
 * public-name: FUN_0101f674
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ble_conn_role_cfg                  @ 0x21001208
 */
/* net-core FUN_0101f674 @ 0x101f674  (parity 300 trials PROVEN) */

unsigned int FUN_0101f674(unsigned char param_1) {
    *(volatile unsigned char *)(((unsigned long)&g_net_ble_conn_role_cfg) /*=0x21001208*/ + 0x19) = param_1;
    return 0;
}
