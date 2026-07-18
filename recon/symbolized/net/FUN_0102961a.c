#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102961a @ 0x0102961a
 * public-name: FUN_0102961a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102961a @ 0x102961a  (CFG-directed candidate) */
/* CPUNET 0x0102961a, true executable extent 0x12. Raw backmap: FUN_0102961a. */
#include <stdint.h>

uint32_t FUN_0102961a(uint8_t *counter)
{
    if (counter[2] != 0u) {
        counter[2]--;
    }
    return counter[2] == 0u;
}
