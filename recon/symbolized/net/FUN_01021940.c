#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021940 @ 0x01021940
 * public-name: FUN_01021940
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01021940 @ 0x01021940
 * Clamp a signed per-channel setting against an optional limit table.
 */
#include <stdint.h>

int32_t FUN_01021940(uint32_t channel, uint32_t index,
                     int32_t requested, uint8_t *result)
{
    if (channel < 5u && result != 0) {
        uint32_t count = channel == 4u ? 0x10u : 0x28u;
        if (index < count) {
            uint32_t table = *(volatile uint32_t *)(0x210016c8u + channel * 4u);
            if (table != 0u) {
                int32_t limit = *(volatile int8_t *)(uintptr_t)(table + index);
                if (limit <= requested) {
                    requested = limit;
                }
            }
            *result = (uint8_t)requested;
            return 0;
        }
    }
    return -22;
}
