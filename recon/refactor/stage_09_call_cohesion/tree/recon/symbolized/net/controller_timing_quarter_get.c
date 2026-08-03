#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027af2 @ 0x01027af2
 * public-name: controller_timing_quarter_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_quarter_get            <= FUN_01027af2 @ 0x01027af2
 */
/* net-core FUN_01027af2 @ 0x1027af2  (CFG-directed candidate) */
#include <stdint.h>
uint32_t controller_timing_quarter_get(uint32_t raw_value)
{
    uint16_t value = (uint16_t)raw_value;
    return (uint16_t)(value >> 2);
}
