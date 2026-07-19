/* readable reconstruction; identity: FUN_0004e964 @ 0x0004e964
 * public-name: gatt_dm_notify_discovery_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_dm_notify_discovery_complete        <= FUN_0004e964 @ 0x0004e964
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

void gatt_dm_notify_discovery_complete(void)
{
    volatile uint32_t *state = (volatile uint32_t *)0x2000a28cu;
    __atomic_fetch_or(state, 2u, __ATOMIC_RELAXED);

    uintptr_t slot = *(volatile uintptr_t *)0x2000a2b0u;
    notify_fn_t notify = slot != 0 ? *(notify_fn_t volatile *)slot : 0;
    if (notify != 0)
        notify(0x2000a154u, *(volatile uint32_t *)0x2000a158u);
}
