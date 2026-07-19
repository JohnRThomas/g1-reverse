#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_bt_gatt_subscribe_params__param_0743   [param_0743; library]
 * Raw function identity: 0x00086f92.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086f92 @ 0x00086f92
 * public-name: gatt_sub_resolve_handle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lseek_r_capture_errno                    <= FUN_00078598 @ 0x00078598
 *   gatt_sub_resolve_handle                  <= FUN_00086f92 @ 0x00086f92
 */
/* Full reconstruction FUN_00086f92 @ 0x86f92 (36-byte extent). */
#include <stdint.h>

extern int32_t lseek_r_capture_errno(uint32_t context, int32_t key);

void gatt_sub_resolve_handle(uint32_t context, uint8_t *record)
{
    int32_t handle = lseek_r_capture_errno(context, *(int16_t *)(record + 0x0e));
    uint16_t flags = *(uint16_t *)(record + 0x0c);

    if (handle == -1) {
        flags &= (uint16_t)~0x1000u;
    } else {
        *(int32_t *)(record + 0x54) = handle;
        flags |= 0x1000u;
    }
    *(uint16_t *)(record + 0x0c) = flags;
}
