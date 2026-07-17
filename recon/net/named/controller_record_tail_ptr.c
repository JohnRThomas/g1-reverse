/* readable reconstruction; identity: FUN_010277a6 @ 0x010277a6
 * public-name: controller_record_tail_ptr
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_record_tail_ptr               <= FUN_010277a6 @ 0x010277a6
 */
/* net-core FUN_010277a6 @ 0x10277a6  (CFG-directed candidate) */

#include <stdint.h>
uintptr_t controller_record_tail_ptr(const uint16_t *entry)
{
    return (uintptr_t)entry + (uint32_t)*entry + 4u;
}
