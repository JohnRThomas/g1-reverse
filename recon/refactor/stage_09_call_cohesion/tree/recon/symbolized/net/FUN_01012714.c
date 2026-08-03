#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01012714 @ 0x01012714
 * public-name: FUN_01012714
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01012714 @ 0x1012714  (CFG-directed candidate) */

#include <stdint.h>
void FUN_01012714(uint8_t *connection, uint8_t *snapshot)
{
    *(uint8_t **)(connection + 0x1c) = snapshot;
    snapshot[9] = connection[0x60];
    *(uint32_t *)(snapshot + 0x0a) = *(uint32_t *)(connection + 0x61);
    *(uint16_t *)(snapshot + 0x0e) = *(uint16_t *)(connection + 0x65);
}
