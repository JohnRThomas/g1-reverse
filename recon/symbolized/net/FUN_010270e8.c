#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010270e8 @ 0x010270e8
 * public-name: FUN_010270e8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010270e8 @ 0x10270e8  (CFG-directed candidate) */
/* CPUNET 0x010270e8, true executable extent 0x62. Raw backmap: FUN_010270e8. */
#include <stdint.h>

extern uint32_t FUN_01026912(uint16_t first, uint16_t second);
extern void controller_packed_cursor_advance(void *owner, void *cursor); /* FUN_0100951c */

uint32_t FUN_010270e8(uint8_t *owner)
{
    if (FUN_01026912(*(uint16_t *)(owner + 4), *(uint16_t *)(owner + 6)) != 0u ||
        *(uint16_t *)(owner + 0x0a) != 0u ||
        *(uint16_t *)(owner + 0x0e) != 0u) {
        return 0u;
    }
    controller_packed_cursor_advance(owner, owner + 4);
    *(uint16_t *)(owner + 0x0e) = 0u;
    return 1u;
}
