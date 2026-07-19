#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_le_serialize_buffer__param_0574        [param_0574; G1-original]
 * Raw function identity: 0x00080eb8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00080eb8 @ 0x00080eb8
 * public-name: sys_put_le64
 * durable-map: recon/catalogs/function_names_app.json
 */
/* sys_put_le64 @ 0x00080eb8; raw FUN_00080eb8 */
#include <stdint.h>

void sys_put_le64(uint64_t value, uint8_t *dst)
{
    uint32_t low = (uint32_t)value;
    uint32_t high = (uint32_t)(value >> 32);

    dst[1] = (uint8_t)(low >> 8);
    dst[0] = (uint8_t)low;
    dst[3] = (uint8_t)(low >> 24);
    dst[2] = 0;
    dst[4] = 0;
    dst[5] = (uint8_t)(high >> 8);
    dst[6] = 0;
    dst[7] = (uint8_t)(high >> 24);
}
