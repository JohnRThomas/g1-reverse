#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e8c8 @ 0x0100e8c8
 * public-name: ble_phy_masks_are_one_hot_or_zero
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ble_phy_masks_are_one_hot_or_zero        <= FUN_0100e8c8 @ 0x0100e8c8
 */
/* net-core ble_phy_masks_are_one_hot_or_zero @ 0x0100e8c8,
 * exact extent 0x1e.
 * Raw/address backmap: FUN_0100e8c8@0x0100e8c8. */
#include <stdbool.h>
#include <stdint.h>
#define ble_phy_masks_are_one_hot_or_zero ble_phy_masks_are_one_hot_or_zero

bool ble_phy_masks_are_one_hot_or_zero(const uint8_t *record)
{
    uint32_t first = record[4] & 7u;
    uint32_t second = record[5] & 7u;

    return (first & (first - 1u)) == 0u &&
           (second & (second - 1u)) == 0u;
}
