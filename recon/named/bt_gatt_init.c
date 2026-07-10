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
    z_impl_k_queue_init(0x20003a28);
    int iVar4 = 0; int iVar5 = 0x2000add4;
    do { iVar4 = iVar4 + 1; net_pkt_skip(0x20003a28, iVar5); iVar5 += 0x14; } while (iVar4 != 10);
    unsigned long long uVar6 = atomic_or_0(0x2000af04, 1);
    unsigned r4 = (unsigned)uVar6 & (unsigned)(uVar6>>32);
    if (r4 != 0) return;
    bt_gatt_service_init();
    *(volatile unsigned*)0x2000af10 = r4;
    *(volatile unsigned*)0x2000af14 = r4;
    FUN_000732d4(0x200063a0, 0x00082cb3);
    k_work_schedule_at_ticks(0x200063a0, 0, 0x148, 0);
    FUN_000732d4(0x20006418, 0x0005b4bd);
    atomic_or_0(0x20006448, 2);
    FUN_000732d4(0x20006350, 0x00082fa7);
    bt_conn_auth_info_cb_register(0x200029f8);
    int iv4 = *(volatile int*)0x2000ad1c;
    *(volatile int*)0x2000ad1c = 0x200029d4;
    *(volatile int*)(0x200029d4+0x20) = iv4;
    return;
}

