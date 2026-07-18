#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01024440 @ 0x01024440
 * public-name: FUN_01024440
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01024440 @ 0x01024440 -- raw backmap retained. */
#include <stdint.h>

/* Convert controller ticks to rounded 32 kHz time units without overflow. */
uint32_t FUN_01024440(uint32_t ticks)
{
    const uint32_t scale = 0x3d09u;
    return (ticks >> 9) * scale +
           (((ticks & 0x1ffu) * scale + 0x100u) >> 9);
}
