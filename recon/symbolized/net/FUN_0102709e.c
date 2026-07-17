#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102709e @ 0x0102709e
 * public-name: FUN_0102709e
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102709e @ 0x0102709e */
#include <stdint.h>

extern uint32_t FUN_01026856(uint32_t);

uint16_t FUN_0102709e(uint32_t context, const uint16_t *record,
                     uint32_t *payload_start)
{
    uint32_t header_size = FUN_01026856(
        *(const uint8_t *)(uintptr_t)(context + 0x13u));
    *payload_start = (uint32_t)(uintptr_t)record + header_size - 3u;
    return *record;
}
