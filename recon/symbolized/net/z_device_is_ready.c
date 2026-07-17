#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b0f0 @ 0x0103b0f0
 * public-name: z_device_is_ready
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_device_is_ready                        <= FUN_0103b0f0 @ 0x0103b0f0
 */
/* net-core FUN_0103b0f0 @ 0x0103b0f0 */
#include <stdint.h>

uint32_t z_device_is_ready(uint32_t object)
{
    const uint8_t *state;
    uint32_t active;

    if (object == 0u) {
        return 0u;
    }
    state = *(const uint8_t **)(uintptr_t)(object + 0xcu);
    active = state[1] & 1u;
    if (active != 0u) {
        active = state[0] == 0u;
    }
    return active;
}
