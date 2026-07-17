#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f834 @ 0x0100f834
 * public-name: controller_procedure_slot_reserve
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_procedure_slot_reserve        <= FUN_0100f834 @ 0x0100f834
 */
/* net-core FUN_0100f834 @ 0x100f834  (CFG-directed candidate) */
/* net-core FUN_0100f834 @ 0x0100f834
 * Readable role: reserve a controller procedure slot and latch its request tag.
 */
#include <stdint.h>

uint32_t controller_procedure_slot_reserve(void *owner, const void *request)
{
    uint8_t *controller = *(uint8_t **)((uint8_t *)owner + 4);
    uint32_t state = *(uint32_t *)(controller + 0xb4);

    if ((state & 8U) != 0U) {
        return 1U;
    }

    *(uint32_t *)(controller + 0xb4) = state | 8U;
    *(uint16_t *)(controller + 0x102) = 0U;
    controller[0x148] = ((const uint8_t *)request)[3];
    controller[0x104] = (uint8_t)(controller[0x104] + 1U);
    return 0U;
}
