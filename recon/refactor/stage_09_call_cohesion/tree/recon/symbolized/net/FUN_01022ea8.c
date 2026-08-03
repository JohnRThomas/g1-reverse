#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01022ea8 @ 0x01022ea8
 * public-name: FUN_01022ea8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01022ea8 @ 0x01022ea8 -- raw backmap retained. */
#include <stdint.h>

extern uint32_t FUN_01024644(void);
extern uint32_t FUN_010245d8(uint32_t);
extern uint32_t FUN_01024440(uint32_t);

uint16_t FUN_01022ea8(void)
{
    uint32_t scheduler_time = FUN_01024644();
    uint32_t ticks = FUN_010245d8(scheduler_time);
    return (uint16_t)FUN_01024440(ticks);
}
