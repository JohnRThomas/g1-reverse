#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039dd0 @ 0x01039dd0
 * public-name: FUN_01039dd0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039dd0 @ 0x01039dd0
 * semantic name: network_context_has_capacity
 * back-map: raw identity FUN_01039dd0
 */
#include <stdint.h>
#include <stdbool.h>

bool FUN_01039dd0(const uint32_t *context)
{
    uint32_t current = context[2];
    uint32_t limit;

    if (((context[4] & 8u) != 0u) || (context[1] >= current))
        limit = context[9];
    else
        limit = context[1];
    return limit != current;
}
