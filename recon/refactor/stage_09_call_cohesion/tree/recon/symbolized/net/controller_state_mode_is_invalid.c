#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01029b24 @ 0x01029b24
 * public-name: controller_state_mode_is_invalid
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_state_mode_is_invalid         <= FUN_01029b24 @ 0x01029b24
 */
/* net-core FUN_01029b24 @ 0x1029b24  (CFG-directed candidate) */
#include <stdint.h>
int32_t controller_state_mode_is_invalid(const volatile uint8_t *state)
{
    uint32_t mode = state[0x10];
    if (mode == 0u || mode == 1u)
        return 0;
    return mode == 7u ? 0 : 1;
}
