#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102971e @ 0x0102971e
 * public-name: FUN_0102971e
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102971e @ 0x102971e  (CFG-directed candidate) */
/* CPUNET 0x0102971e, true executable extent 0x1a. Raw backmap: FUN_0102971e. */
#include <stdint.h>

uint32_t FUN_0102971e(uint32_t mask)
{
    if ((mask & 1u) != 0u) {
        return 1u;
    }
    if ((mask & 2u) != 0u) {
        return 2u;
    }
    return (mask & 4u) != 0u ? 8u : 0u;
}
