/* readable reconstruction; identity: FUN_01028112 @ 0x01028112
 * public-name: FUN_01028112
 * durable-map: recon/catalogs/function_names_net.json
 */
/* controller_access_address_conflict @ 0x01028112; raw FUN_01028112.
 * Retained private-controller reconstruction; exact executable extent 0x22.
 */
#include <stdint.h>

extern uint32_t FUN_0100f6b0(uint32_t value);
#define controller_access_address_conflict FUN_01028112

uint32_t controller_access_address_conflict(
    uint32_t candidate, uint32_t active, uint32_t allow_one_bit_difference)
{
    if (candidate == active) {
        return 1u;
    }
    if (allow_one_bit_difference != 0u) {
        return FUN_0100f6b0(candidate ^ active) < 2u ? 1u : 0u;
    }
    return 0u;
}
