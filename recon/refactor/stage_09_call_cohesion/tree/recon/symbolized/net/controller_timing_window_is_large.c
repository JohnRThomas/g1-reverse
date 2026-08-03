#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e7e0 @ 0x0100e7e0
 * public-name: controller_timing_window_is_large
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_window_is_large        <= FUN_0100e7e0 @ 0x0100e7e0
 */
/* net-core controller_timing_window_is_large @ 0x0100e7e0,
 * exact extent 0x26.
 * Raw/address backmap: FUN_0100e7e0@0x0100e7e0. */
#include <stdbool.h>
#include <stdint.h>
#define controller_timing_window_is_large controller_timing_window_is_large

bool controller_timing_window_is_large(const uint8_t *record)
{
    return *(const uint16_t *)(record + 8) >= 27u &&
           *(const uint16_t *)(record + 10) >= 328u &&
           *(const uint16_t *)(record + 4) >= 27u &&
           *(const uint16_t *)(record + 6) >= 328u;
}
