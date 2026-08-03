#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010218f0 @ 0x010218f0
 * public-name: FUN_010218f0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_ops_table_ptr                @ 0x21000530
 */
/* net-core FUN_010218f0 @ 0x10218f0  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218f0(void) {
    uint32_t v = *(volatile uint32_t *)((unsigned long)&g_net_radio_ops_table_ptr) /*=0x21000530*/;
    code fn = *(code*)(v + 0x18);
    fn();
}
