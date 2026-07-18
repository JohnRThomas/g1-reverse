/* readable reconstruction; identity: FUN_0005a954 @ 0x0005a954
 * public-name: bt_gatt_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_schedule_at_ticks                 <= FUN_000531cc @ 0x000531cc
 *   bt_conn_auth_info_cb_register            <= FUN_00057330 @ 0x00057330
 *   bt_gatt_service_init                     <= FUN_00059cb4 @ 0x00059cb4
 *   bt_gatt_init                             <= FUN_0005a954 @ 0x0005a954
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 * address symbols (name @ address):
 *   rodata_82cb3                             @ 0x00082cb3
 *   g_200029d4                               @ 0x200029d4
 *   g_200029f8                               @ 0x200029f8
 *   g_bt_gatt_db_hash_work                   @ 0x200063a0
 *   g_20006418                               @ 0x20006418
 *   g_bt_gatt_flags                          @ 0x20006448
 *   gatt_service_init_guard                  @ 0x2000af04
 *   g_bt_gatt_callback_list_head             @ 0x2000af10
 *   g_2000af14                               @ 0x2000af14
 */
/* Reconstructed FUN_0005a954 @ 0x0005a954 (bt_gatt_init).
 * Raw/address backmap: FUN_0005a954 @ 0x0005a954, extent 0x00000058.
 */
#include <stdint.h>
extern uint32_t atomic_or_0(volatile uint32_t *, uint32_t); /* atomic_or */
extern void bt_gatt_service_init(void);                              /* bt_gatt_service_init */
extern void FUN_000732d4(void *, void *);                    /* k_work_init_delayable */
extern void k_work_schedule_at_ticks(void *, uint32_t, uint32_t);        /* memset */
extern void bt_conn_auth_info_cb_register(void *);                            /* bt_conn_auth_info_cb_register */
extern void FUN_00056e24(void *);                            /* bt_conn_cb_register */

void bt_gatt_init(void)
{
    if ((atomic_or_0((volatile uint32_t *)0x2000af04U, 1U) & 1U) != 0U)
        return;
    bt_gatt_service_init();
    *(volatile uint32_t *)0x2000af10U = 0;
    *(volatile uint32_t *)0x2000af14U = 0;
    FUN_000732d4((void *)0x20006418U, (void *)0x00082cb3U);
    k_work_schedule_at_ticks((void *)0x200063a0U, 0U, 0x148U);
    FUN_000732d4((void *)0x20006448U, (void *)0x00082fb5U);
    (void)atomic_or_0((volatile uint32_t *)0x20006448U, 2U);
    FUN_000732d4((void *)0x200064b8U, (void *)0x00082ff9U);
    bt_conn_auth_info_cb_register((void *)0x200029f8U);
    FUN_00056e24((void *)0x200029d4U);
}
