#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102741e @ 0x0102741e
 * public-name: controller_handle_slot_find_from
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_find_from         <= FUN_0102741e @ 0x0102741e
 */
/* net-core FUN_0102741e @ 0x102741e  (CFG-directed candidate) */
#include <stdint.h>
uint32_t controller_handle_slot_find_from(const volatile uint8_t *table, uint16_t value,
                       uint32_t raw_start_slot)
{
    uint8_t start_slot = (uint8_t)raw_start_slot;
    uint8_t slot = start_slot;
    do {
        if (*(const volatile uint16_t *)(table + 10u + (uint32_t)slot * 2u) == value)
            return slot;
        uint32_t next = (uint32_t)slot + 1u;
        uint32_t count = table[2];
        slot = (uint8_t)(next - (next / count) * count);
    } while (slot != start_slot);
    return 0xffu;
}
