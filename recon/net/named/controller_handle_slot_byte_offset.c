/* readable reconstruction; identity: FUN_010274d0 @ 0x010274d0
 * public-name: controller_handle_slot_byte_offset
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_handle_slot_byte_offset       <= FUN_010274d0 @ 0x010274d0
 */
/* net-core FUN_010274d0 @ 0x10274d0  (CFG-directed candidate) */

#include <stdint.h>
/* Readable role: controller_handle_slot_byte_offset. Raw back-map: FUN_010274d0 @ 0x010274d0. */
uint32_t controller_handle_slot_byte_offset(uint32_t raw_slot)
{
    uint8_t slot = (uint8_t)raw_slot;
    return ((uint32_t)slot + 5u) * 2u;
}
