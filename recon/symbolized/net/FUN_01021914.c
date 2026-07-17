#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021914 @ 0x01021914
 * public-name: FUN_01021914
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_ops_table_ptr                @ 0x21000530
 */
/* net-core FUN_01021914 @ 0x1021914  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01021914(void) {
    uint32_t v = *(volatile uint32_t*)((unsigned long)&g_net_radio_ops_table_ptr) /*=0x21000530*/;
    code fn = *(code*)(v + 0x2c);
    fn();
}
