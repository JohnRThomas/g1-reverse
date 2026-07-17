#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f8cc @ 0x0101f8cc
 * public-name: FUN_0101f8cc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_flags_bitmap64                     @ 0x21000020
 */
/* net-core FUN_0101f8cc @ 0x101f8cc  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint64_t * const DAT_0101f8d4 = (volatile uint64_t *)((unsigned long)&g_net_flags_bitmap64) /*=0x21000020*/;
uint64_t FUN_0101f8cc(void) {
    return *DAT_0101f8d4;
}
