#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f784 @ 0x0100f784
 * public-name: controller_procedure_counters_reset
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_procedure_counters_reset      <= FUN_0100f784 @ 0x0100f784
 */
/* net-core FUN_0100f784 @ 0x100f784  (CFG-directed candidate) */
/* Role: reset controller timing counters. Back-map: FUN_0100f784. */
#include <stdint.h>
void controller_procedure_counters_reset(void *owner)
{
    uint8_t *state = *(uint8_t **)((uint8_t *)owner + 4);
    state[0xc5] = 0;
    state[0x100] = 0;
    *(uint16_t *)(state + 0xfc) = 0;
}
