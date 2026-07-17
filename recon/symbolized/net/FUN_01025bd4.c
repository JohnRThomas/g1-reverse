#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025bd4 @ 0x01025bd4
 * public-name: FUN_01025bd4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_driver_api_ptr                     @ 0x21000574
 */
/* net-core FUN_01025bd4 @ 0x1025bd4  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01025bd4(void) {
    uint32_t v = *(volatile uint32_t*)((unsigned long)&g_net_driver_api_ptr) /*=0x21000574*/;
    code fn = *(code*)(v + 0x10);
    fn();
}
