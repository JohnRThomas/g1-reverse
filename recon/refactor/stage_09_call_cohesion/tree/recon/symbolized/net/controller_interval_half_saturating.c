#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027b0c @ 0x01027b0c
 * public-name: controller_interval_half_saturating
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_interval_half_saturating      <= FUN_01027b0c @ 0x01027b0c
 */
/* net-core FUN_01027b0c @ 0x1027b0c  (CFG-directed candidate) */

#include <stdint.h>
/* Readable role: controller_interval_half_saturating. Raw back-map: FUN_01027b0c @ 0x01027b0c. */
uint16_t controller_interval_half_saturating(uint32_t raw_value)
{
    uint16_t value = (uint16_t)raw_value;
    return value < 0x1feu ? (uint16_t)(value >> 1) : 0xffu;
}
