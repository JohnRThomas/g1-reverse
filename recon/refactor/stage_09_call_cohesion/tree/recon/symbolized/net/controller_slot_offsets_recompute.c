#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010095c0 @ 0x010095c0
 * public-name: controller_slot_offsets_recompute
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_slot_offsets_recompute        <= FUN_010095c0 @ 0x010095c0
 */
/* net-core FUN_010095c0 @ 0x10095c0  (CFG-directed candidate) */

#include <stdint.h>
extern void sdc_assertion_fail(uint32_t group, uint32_t line);
void controller_slot_offsets_recompute(void)
{
    volatile uint8_t * volatile *slots = (volatile uint8_t * volatile *)G1N_21000b7c;
    for (int index = 10; index >= 0; --index) {
        volatile uint8_t *entry = slots[index];
        if (entry == 0) continue;
        uint8_t group = entry[4];
        if (group == 0xffu) {
            entry[4] = 0u;
            continue;
        }
        uint32_t offset = 0u;
        for (int earlier = index - 1; earlier >= 0; --earlier) {
            volatile uint8_t *prior = slots[earlier];
            if (prior != 0 && prior[4] == group) offset += prior[2];
        }
        if (offset > 0xffu) sdc_assertion_fail(0x17u, 0xfau);
        entry[4] = (uint8_t)offset;
    }
}
