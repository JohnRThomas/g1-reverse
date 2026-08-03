#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01013d90 @ 0x01013d90
 * public-name: FUN_01013d90
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01013d90 @ 0x01013d90
 * Readable identity: controller_fixed_packet_time_get.
 * Raw callee backmap: FUN_0100f5b4=controller_payload_time_get.
 */
#include <stdint.h>

extern uint32_t FUN_0100f5b4(const uint32_t *timing, uint32_t overhead);

#define controller_payload_time_get FUN_0100f5b4

uint32_t FUN_01013d90(const uint32_t *timing)
{
    uint32_t duration = controller_payload_time_get(timing, 0x27cu);

    if (duration >= 0xa90u) {
        duration = 0xa90u;
    }
    return (uint16_t)duration;
}
