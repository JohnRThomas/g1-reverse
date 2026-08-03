#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010268ce @ 0x010268ce
 * public-name: FUN_010268ce
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010268ce @ 0x010268ce, exact Thumb extent 0x44 bytes. */
#include <stdint.h>

/* True when two wrapped 15-bit positions agree but occupy opposite epochs. */
uint8_t FUN_010268ce(uint16_t first, uint16_t second)
{
    uint16_t difference = (uint16_t)(first ^ second);
    return (uint8_t)(((difference & 0x7fffu) == 0u) &&
                     ((int16_t)difference < 0));
}
