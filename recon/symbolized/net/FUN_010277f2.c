#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010277f2 @ 0x010277f2
 * public-name: FUN_010277f2
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010277f2 @ 0x10277f2  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0102763a(uint16_t, uint16_t, uint16_t); /* =FUN_0102763a */
uint32_t FUN_010277f2(uint16_t first, uint16_t second)
{
    volatile uint16_t saved_first = first;
    volatile uint16_t saved_second = second;
    return (uint16_t)((FUN_0102763a(saved_first, 9u, saved_second) + 3u) & ~3u);
}
