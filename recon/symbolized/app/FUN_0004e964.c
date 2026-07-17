#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e964 @ 0x0004e964
 * public-name: FUN_0004e964
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   cur_service_val                          @ 0x2000a154
 *   g_gatt_dm_context                        @ 0x2000a158
 *   g_gatt_dm_in_progress_flag               @ 0x2000a28c
 *   g_gatt_dm_svc_range_end                  @ 0x2000a2b0
 */
/* Reconstructed FUN_0004e964 @ 0x4e964, exact extent 34 bytes.
 * CFG_VERIFY_CALL_ARITIES=2 */
#include <stdint.h>

typedef void (*notify_fn_t)(uintptr_t object, uint32_t value);

void FUN_0004e964(void)
{
    volatile uint32_t *state = (volatile uint32_t *)((unsigned long)&g_gatt_dm_in_progress_flag) /*=0x2000a28c*/;
    __atomic_fetch_or(state, 2u, __ATOMIC_RELAXED);

    uintptr_t slot = *(volatile uintptr_t *)((unsigned long)&g_gatt_dm_svc_range_end) /*=0x2000a2b0*/;
    notify_fn_t notify = slot != 0 ? *(notify_fn_t volatile *)slot : 0;
    if (notify != 0)
        notify(((unsigned long)&cur_service_val) /*=0x2000a154*/, *(volatile uint32_t *)((unsigned long)&g_gatt_dm_context) /*=0x2000a158*/);
}
