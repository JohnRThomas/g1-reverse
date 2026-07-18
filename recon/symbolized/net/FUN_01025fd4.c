#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025fd4 @ 0x01025fd4
 * public-name: FUN_01025fd4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_feature_bit_enabled           <= FUN_0100938c @ 0x0100938c
 */
/* CPUNET two-stage controller feature gate @ 0x01025fd4.
 * Raw back-map: FUN_01025fd4=controller_feature_pair_enabled;
 * true executable extent 0x1c. */
#include <stdint.h>

extern uint32_t FUN_0100930c(uint32_t identifier);
extern uint32_t controller_feature_bit_enabled(uint32_t identifier);

uint32_t FUN_01025fd4(uint32_t type, uint32_t subtype)
{
    if (FUN_0100930c(type) != 0u && type == 0x3eu)
        return controller_feature_bit_enabled(subtype);
    return 0u;
}
