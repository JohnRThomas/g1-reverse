#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a954 @ 0x0005a954
 * public-name: bt_gatt_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_schedule_at_ticks                 <= FUN_000531cc @ 0x000531cc
 *   bt_conn_cb_register                      <= FUN_00056e24 @ 0x00056e24
 *   bt_conn_auth_info_cb_register            <= FUN_00057330 @ 0x00057330
 *   bt_gatt_service_init                     <= FUN_00059cb4 @ 0x00059cb4
 *   bt_gatt_init                             <= FUN_0005a954 @ 0x0005a954
 *   k_work_init_delayable                    <= FUN_000732d4 @ 0x000732d4
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 * address symbols (name @ address):
 *   rodata_5b4bd                             @ 0x0005b4bd
 *   rodata_82cb3                             @ 0x00082cb3
 *   ADDR_gatt_store_ccc_cf_triple_THUMB      @ 0x00082fa7
 *   g_200029d4                               @ 0x200029d4
 *   g_200029f8                               @ 0x200029f8
 *   g_bt_gatt_delayed_store_work             @ 0x20006350
 *   g_bt_gatt_db_hash_work                   @ 0x200063a0
 *   g_bt_gatt_sc_work                        @ 0x20006418
 *   g_bt_gatt_flags                          @ 0x20006448
 *   gatt_service_init_guard                  @ 0x2000af04
 *   g_bt_gatt_callback_list_head             @ 0x2000af10
 *   g_2000af14                               @ 0x2000af14
 */
/* Reconstructed FUN_0005a954 @ 0x0005a954 (bt_gatt_init).
 * Raw/address backmap: FUN_0005a954 @ 0x0005a954, extent 0x00000058.
 */
#include <stdint.h>
extern int atomic_or_0(volatile long*, long); /* atomic_or */
extern void bt_gatt_service_init(void);                              /* bt_gatt_service_init */
extern void k_work_init_delayable(void *, void *);                    /* k_work_init_delayable */
/* k_work_schedule(dwork, k_timeout_t).  The 64-bit timeout is aligned to
 * r2/r3 by AAPCS, so retain the otherwise-unused r1 slot explicitly. */
extern void k_work_schedule_at_ticks(void *, uint32_t, uint64_t);         /* k_work_schedule */
extern void bt_conn_auth_info_cb_register(void *);                            /* bt_conn_auth_info_cb_register */
extern void bt_conn_cb_register(void *);                            /* bt_conn_cb_register */

void bt_gatt_init(void)
{
    if ((atomic_or_0((volatile uint32_t *)((unsigned long)&gatt_service_init_guard) /*=0x2000af04*/, 1U) & 1U) != 0U)
        return;
    bt_gatt_service_init();
    *(volatile uint32_t *)((unsigned long)&g_bt_gatt_callback_list_head) /*=0x2000af10*/ = 0;
    *(volatile uint32_t *)((unsigned long)&g_2000af14) /*=0x2000af14*/ = 0;
    /* db_hash.work @ db_hash+0x20; handler db_hash_process @0x82cb2. */
    k_work_init_delayable((void *)((unsigned long)&g_bt_gatt_db_hash_work) /*=0x200063a0*/, (void *)((unsigned long)&rodata_82cb3) /*=0x82cb3*/);
    k_work_schedule_at_ticks((void *)((unsigned long)&g_bt_gatt_db_hash_work) /*=0x200063a0*/, 0U, 0x148ULL);
    /* gatt_sc.work @ gatt_sc+0x20; handler sc_process @0x5b4bc. */
    k_work_init_delayable((void *)((unsigned long)&g_bt_gatt_sc_work) /*=0x20006418*/, (void *)((unsigned long)&rodata_5b4bd) /*=0x5b4bd*/);
    /* gatt_sc.flags @ gatt_sc+0x50: atomic flags, not a k_work object. */
    (void)atomic_or_0((volatile uint32_t *)((unsigned long)&g_bt_gatt_flags) /*=0x20006448*/, 2U);
    /* gatt_delayed_store.work @ gatt_delayed_store+0x28. */
    k_work_init_delayable((void *)((unsigned long)&g_bt_gatt_delayed_store_work) /*=0x20006350*/, (void *)ADDR_gatt_store_ccc_cf_triple_THUMB /*=0x82fa7*/);
    bt_conn_auth_info_cb_register((void *)((unsigned long)&g_200029f8) /*=0x200029f8*/);
    bt_conn_cb_register((void *)((unsigned long)&g_200029d4) /*=0x200029d4*/);
}
