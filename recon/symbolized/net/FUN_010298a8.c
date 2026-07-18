#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010298a8 @ 0x010298a8
 * public-name: FUN_010298a8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010298a8 @ 0x010298a8
 * Normalize controller mode flags to one supported mode.
 */
#include <stdint.h>

uint32_t FUN_010298a8(uint32_t mode)
{
    if (mode != 1u && mode != 2u) {
        mode &= 0x0cu;
        if (mode != 0u) {
            mode = 4u;
        }
    }
    return mode;
}
