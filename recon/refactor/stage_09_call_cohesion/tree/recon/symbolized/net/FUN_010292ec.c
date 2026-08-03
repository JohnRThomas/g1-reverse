#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010292ec @ 0x010292ec
 * public-name: FUN_010292ec
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private handle-state activation @ 0x010292ec.
 * True executable extent [0x010292ec,0x0102931a).
 * Raw back-map: FUN_010292ec@0x010292ec. */
#include <stdint.h>

extern uint8_t *controller_typed_handle_lookup(uint16_t handle, unsigned type); /* FUN_01009d18 */

unsigned FUN_010292ec(const uint16_t *handle)
{
    uint8_t *entry = controller_typed_handle_lookup(*handle, 1);
    if (entry == 0)
        return 2;
    if (entry[0x3a0] != 0)
        return 0x0c;
    if ((uint8_t)(entry[0xc6] - 0x16u) > 1u)
        return 0x0c;
    entry[0x3a0] = 2;
    return 0;
}
