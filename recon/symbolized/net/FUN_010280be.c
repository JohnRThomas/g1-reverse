#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010280be @ 0x010280be
 * public-name: FUN_010280be
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010280be @ 0x010280be
 * Invoke the controller helper with the enabled selector.
 */
#include <stdint.h>

extern uint32_t FUN_01028034(uint32_t context, uint32_t enabled);

uint32_t FUN_010280be(uint32_t context)
{
    return FUN_01028034(context, 1u);
}
