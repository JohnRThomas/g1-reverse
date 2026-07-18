#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027ed4 @ 0x01027ed4
 * public-name: FUN_01027ed4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* FUN_01027ed4 @ 0x01027ed4: fixed-mode wrapper around the private helper. */
#include <stdint.h>

extern uint32_t FUN_01027e1c(uint32_t first, uint32_t second, uint32_t mode);

uint32_t FUN_01027ed4(uint32_t first, uint32_t second)
{
    return FUN_01027e1c(first, second, 1u);
}

/* Raw identity/back-map: FUN_01027ed4 @ 0x01027ed4, true extent 0x1e. */
