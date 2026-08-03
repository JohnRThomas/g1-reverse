#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102d6e0 @ 0x0102d6e0
 * public-name: FUN_0102d6e0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   get_ept_slot_with_name                   <= FUN_01039f4c @ 0x01039f4c
 * address symbols (name @ address):
 *   rodata_103cf0a                           @ 0x0103cf0a
 */
/* net-core FUN_0102d6e0 @ 0x0102d6e0 */
#include <stdint.h>

extern int get_ept_slot_with_name(uint32_t, ...);

uint32_t FUN_0102d6e0(uint32_t state, uint32_t *record, uint32_t key,
                      uint32_t argument)
{
    int found = get_ept_slot_with_name(state, key, key, argument);
    uint32_t reused = found != 0;
    if (!reused) {
        found = get_ept_slot_with_name(state, ((unsigned long)&rodata_103cf0a) /*=0x103cf0a*/);
    }
    *record = (uint32_t)found;
    return reused;
}
