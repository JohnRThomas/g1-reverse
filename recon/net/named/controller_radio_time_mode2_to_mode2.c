/* readable reconstruction; identity: FUN_01021634 @ 0x01021634
 * public-name: controller_radio_time_mode2_to_mode2
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_radio_time_mode2_to_mode2     <= FUN_01021634 @ 0x01021634
 */
/* net-core FUN_01021634 @ 0x1021634  (CFG-directed candidate) */
/* CPUNET controller_radio_time_mode2_to_mode2 @ 0x01021634, extent 0x1c.
 * Raw backmap and exported reconstruction spelling: FUN_01021634. */
#include <stdint.h>

extern uint32_t radio_phy_airtime_base_get(uint32_t phy); /* FUN_010209f0 */

int32_t controller_radio_time_mode2_to_mode2(int32_t ticks, uint32_t phy)
{
    uint32_t rounded = radio_phy_airtime_base_get(phy) + 999u;
    uint32_t milliseconds = (uint32_t)(((uint64_t)0x10624dd3u * rounded) >> 38);
    return (ticks - 2) - (int32_t)milliseconds;
}
