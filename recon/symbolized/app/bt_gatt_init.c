#include "g1_app_symbols.h"
/* named: bt_gatt_init */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed bt_gatt_init @ 0x59690  (parity: 300/300 trials, PROVEN) */

extern unsigned long long atomic_or_0(unsigned a, int b);
extern void z_impl_k_queue_init(unsigned a);
extern void net_pkt_skip(unsigned a, int b);
extern void bt_gatt_service_init(void);
extern void FUN_000732d4(unsigned a, unsigned b);
extern void k_work_schedule_at_ticks(unsigned a, unsigned b, int c, int d);
extern void bt_conn_auth_info_cb_register(unsigned a);
void bt_gatt_init(void){
    z_impl_k_queue_init(((uintptr_t)&g_bt_att_pool) /*=0x20003a28*/);
    int iVar4 = 0; int iVar5 = ((uintptr_t)&g_bt_gatt_indicate_ctx_pool) /*=0x2000add4*/;
    do { iVar4 = iVar4 + 1; net_pkt_skip(((uintptr_t)&g_bt_att_pool) /*=0x20003a28*/, iVar5); iVar5 += 0x14; } while (iVar4 != 10);
    unsigned long long uVar6 = atomic_or_0(((uintptr_t)&gatt_service_init_guard) /*=0x2000af04*/, 1);
    unsigned r4 = (unsigned)uVar6 & (unsigned)(uVar6>>32);
    if (r4 != 0) return;
    bt_gatt_service_init();
    *(volatile unsigned*)((uintptr_t)&g_bt_gatt_callback_list_head) /*=0x2000af10*/ = r4;
    *(volatile unsigned*)((uintptr_t)&g_bt_gatt_cb_slist_tail) /*=0x2000af14*/ = r4;
    FUN_000732d4(((uintptr_t)&g_bt_gatt_db_hash_work) /*=0x200063a0*/, ((uintptr_t)&rodata_82cb3) /*=0x82cb3*/);
    k_work_schedule_at_ticks(((uintptr_t)&g_bt_gatt_db_hash_work) /*=0x200063a0*/, 0, 0x148, 0);
    FUN_000732d4(((uintptr_t)&g_bt_gatt_db_hash_work_6418) /*=0x20006418*/, ((uintptr_t)&tbl_5b49c) /*=0x5b4bd*/);
    atomic_or_0(((uintptr_t)&g_bt_gatt_flags) /*=0x20006448*/, 2);
    FUN_000732d4(((uintptr_t)&g_bt_gatt_delayed_store_work) /*=0x20006350*/, ((uintptr_t)&rodata_82fa7) /*=0x82fa7*/);
    bt_conn_auth_info_cb_register(((uintptr_t)&g_bt_gatt_auth_info_cb) /*=0x200029f8*/);
    int iv4 = *(volatile int*)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    *(volatile int*)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/ = ((uintptr_t)&g_bt_gatt_conn_cb) /*=0x200029d4*/;
    *(volatile int*)(((uintptr_t)&g_bt_gatt_conn_cb) /*=0x200029d4*/+0x20) = iv4;
    return;
}

