/* readable reconstruction; identity: FUN_0100f6e8 @ 0x0100f6e8
 * public-name: controller_byte_popcount
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_byte_popcount                 <= FUN_0100f6e8 @ 0x0100f6e8
 */
/* net-core FUN_0100f6e8 @ 0x100f6e8  (CFG-directed candidate) */
/* Role: population count of the low controller byte. Back-map: FUN_0100f6e8. */
#include <stdint.h>
uint32_t controller_byte_popcount(uint32_t value)
{
    value = (value & 0x55u) + ((value >> 1) & 0x55u);
    value = (value & 0x33u) + ((value >> 2) & 0x33u);
    return (value & 0x0fu) + (value >> 4);
}
