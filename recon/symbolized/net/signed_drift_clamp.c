#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f69c @ 0x0100f69c
 * public-name: signed_drift_clamp
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   signed_drift_clamp                       <= FUN_0100f69c @ 0x0100f69c
 */
/* net-core FUN_0100f69c @ 0x100f69c  (CFG-directed candidate) */

#include <stdint.h>

int32_t signed_drift_clamp(int32_t drift, int32_t limit)
{
    if (drift < 0) {
        int32_t lower = (int32_t)(0U - (uint32_t)limit);
        if (drift >= lower)
            return drift;
        return (int16_t)lower;
    }
    if (drift < limit)
        return drift;
    return (int16_t)limit;
}
