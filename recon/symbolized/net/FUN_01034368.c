#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01034368 @ 0x01034368
 * public-name: FUN_01034368
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01034368 @ 0x1034368 — true CFG extent 48 bytes (ends 0x1034398) */
#include <stdint.h>

uint32_t FUN_01034368(volatile uint32_t *flags, uint32_t bit_index)
{
    uint32_t shift = bit_index & 0xffu;
    uint32_t mask = shift < 32u ? 1u << shift : 0u;
    if (*flags & mask)
        return 0x0bad0004u;
    __atomic_fetch_or(flags, mask, __ATOMIC_RELAXED);
    return 0x0bad0000u;
}
