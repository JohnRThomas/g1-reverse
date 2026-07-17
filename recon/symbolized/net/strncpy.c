#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b5a4 @ 0x0103b5a4
 * public-name: strncpy
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   strncpy                                  <= FUN_0103b5a4 @ 0x0103b5a4
 */
/* net-core FUN_0103b5a4 @ 0x0103b5a4 */
#include <stdint.h>

extern void FUN_0103b62e(uint8_t *, uint32_t, uint32_t);

uint8_t *strncpy(uint8_t *destination, const uint8_t *source,
                     uint32_t capacity)
{
    uint8_t *out = destination;

    while (capacity != 0u) {
        uint8_t value = *source++;
        --capacity;
        *out++ = value;
        if (value == 0u) {
            break;
        }
    }
    FUN_0103b62e(out, 0u, capacity);
    return destination;
}
