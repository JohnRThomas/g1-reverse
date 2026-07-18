#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010245d8 @ 0x010245d8
 * public-name: FUN_010245d8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010245d8 @ 0x010245d8 -- raw backmap retained. */
#include <stdint.h>

/* Inverse rounded fixed-point conversion used by the controller scheduler. */
uint32_t FUN_010245d8(uint32_t time_units)
{
    uint32_t coarse = ((time_units >> 13) * 0x8637u) >> 16;
    uint32_t remainder = time_units - coarse * 0x3d09u;
    uint32_t fine = (remainder * 0x10c6fu + 0x10c6eu) >> 21;
    uint32_t ticks = coarse << 9;

    if (((fine * 0x3d09u) >> 9) < remainder)
        ++ticks;
    return ticks + fine;
}
