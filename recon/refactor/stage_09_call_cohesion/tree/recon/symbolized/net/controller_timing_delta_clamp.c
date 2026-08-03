#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027b32 @ 0x01027b32
 * public-name: controller_timing_delta_clamp
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_interval_half_saturating      <= FUN_01027b0c @ 0x01027b0c
 *   controller_timing_delta_clamp            <= FUN_01027b32 @ 0x01027b32
 */
/* net-core FUN_01027b32 @ 0x1027b32  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t controller_interval_half_saturating(uint16_t value);
uint32_t controller_timing_delta_clamp(uint32_t raw_value)
{
    uint16_t value = (uint16_t)raw_value;
    uint16_t base = (uint16_t)controller_interval_half_saturating(value);
    int32_t delta = (int32_t)(uint32_t)value - (int32_t)(uint32_t)base;
    if (delta < 0x672)
        return (uint16_t)delta;
    return 0x672u;
}
