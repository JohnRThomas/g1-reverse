#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055aac @ 0x00055aac
 * public-name: legacy_advertising_connection_restart
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_id_set_adv_random_addr                <= FUN_00055454 @ 0x00055454
 *   adv_is_directed                          <= FUN_00055698 @ 0x00055698
 *   ble_conn_addr_resolve_or_create          <= FUN_000556b0 @ 0x000556b0
 *   legacy_advertising_connection_restart    <= FUN_00055aac @ 0x00055aac
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_set_state                       <= FUN_00056704 @ 0x00056704
 *   deref_conn_field0                        <= FUN_0008117a @ 0x0008117a
 *   atomic_and_1                             <= FUN_00081180 @ 0x00081180
 *   bt_le_adv_set_enable_legacy              <= FUN_000812d2 @ 0x000812d2
 * address symbols (name @ address):
 *   rodata_880f8                             @ 0x000880f8
 *   rodata_f3857                             @ 0x000f3857   [INLINED -- G6 literal batch]
 *   g_bt_le_legacy_adv                       @ 0x20002018
 *   g_ble_adv_ctx_flags                      @ 0x20002028
 */
/* Reconstructed FUN_00055aac @ 0x55aac
 * Readable identity: legacy_advertising_connection_restart.
 * Raw/address backmap: FUN_00055aac @ 0x00055aac.
 */
#include <stdint.h>

extern uint32_t deref_conn_field0(volatile uint32_t *); /* atomic_get */
extern int ble_conn_addr_resolve_or_create(void *, void *); /* connection lookup/create */
extern uint32_t adv_is_directed(void *); /* adv_is_directed */
extern int bt_id_set_adv_random_addr(void *, uint32_t, uint32_t, void *); /* legacy advertising configure */
extern void z_log_msg_runtime_create(uint32_t, uint32_t, const void *, uint32_t);
extern int bt_le_adv_set_enable_legacy(void *, uint32_t); /* bt_le_adv_set_enable_legacy */
extern void ble_conn_unref(void *); /* bt_conn_unref */
extern void ble_conn_set_state(void *, uint32_t); /* bt_conn_set_state */
extern uint32_t atomic_and_1(volatile uint32_t *, uint32_t); /* atomic_and */

void legacy_advertising_connection_restart(void)
{
    volatile uint32_t *const flags = (volatile uint32_t *)((unsigned long)&g_ble_adv_ctx_flags) /*=0x20002028*/;
    void *connection = 0;
    uint8_t option = 0;

    if ((deref_conn_field0(flags) & 0x4000U) == 0U) return;
    if ((deref_conn_field0(flags) & 0x80U) != 0U) return;
    if ((deref_conn_field0(flags) & 0x400U) == 0U) return;

    if (ble_conn_addr_resolve_or_create((void *)((unsigned long)g_bt_le_legacy_adv) /*=0x20002018*/, &connection) != 0) return;
    {
        uint32_t directed = adv_is_directed((void *)((unsigned long)g_bt_le_legacy_adv) /*=0x20002018*/);
        uint32_t mode = ((((deref_conn_field0(flags) >> 14) & 1U) ^ 1U) << 1);
        if ((deref_conn_field0(flags) & 0x400U) != 0U) mode |= 1U;
        if ((deref_conn_field0(flags) & 0x2000U) != 0U) mode |= 4U;

        {
            int error = bt_id_set_adv_random_addr((void *)((unsigned long)g_bt_le_legacy_adv) /*=0x20002018*/, mode,
                                      directed, &option);
            if (error != 0) {
                uint32_t package[3] = { 3U, ((unsigned long)"Controller cannot resume connectable advertising (%d)") /*=0xf3857*/, (uint32_t)error };
                z_log_msg_runtime_create(((unsigned long)&rodata_880f8) /*=0x880f8*/, 0x1840U, package, 0U);
                return;
            }
        }

        if (bt_le_adv_set_enable_legacy((void *)((unsigned long)g_bt_le_legacy_adv) /*=0x20002018*/, 1U) == 0) {
            ble_conn_unref(connection);
            return;
        }
        ble_conn_set_state(connection, directed);
        {
            uint32_t old = atomic_and_1(flags, 0xffffbfffU);
            ble_conn_unref(connection);
            if ((old & 0x4000U) != 0U) {
                (void)__atomic_fetch_or((uint32_t *)flags, 0x4000U,
                                        __ATOMIC_SEQ_CST);
            }
        }
    }
}
