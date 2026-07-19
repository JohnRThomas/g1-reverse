/* readable reconstruction; identity: FUN_00057358 @ 0x00057358
 * public-name: bt_conn_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_init                             <= FUN_00057358 @ 0x00057358
 *   bt_l2cap_init                            <= FUN_000579d0 @ 0x000579d0
 *   bt_att_init                              <= FUN_00059690 @ 0x00059690
 *   smp_update_bond_flag                     <= FUN_0005e5b8 @ 0x0005e5b8
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   g_bt_conn_tx_pending_cnt                 @ 0x20003a60
 *   g_bt_conn_pool                           @ 0x2000ac7c
 */
/* Reconstructed FUN_00057358 @ 0x57358  (parity: 300/300 trials, PROVEN) */

#define z_impl_k_queue_init z_impl_k_queue_init
extern void z_impl_k_queue_init(void *queue);
extern void net_pkt_skip(unsigned int, unsigned int);
extern void bt_att_init(void);
extern int smp_update_bond_flag(void);
extern void bt_l2cap_init(void);

int bt_conn_init(void)
{
    z_impl_k_queue_init((void *)0x20003a60UL);
    unsigned int uVar1 = 0x20003a60UL;
    unsigned int iVar3 = 0x2000ac7cUL;
    int iVar2 = 0;
    do {
        iVar2 = iVar2 + 1;
        net_pkt_skip(uVar1, iVar3);
        iVar3 = iVar3 + 0x10;
    } while (iVar2 != 10);
    bt_att_init();
    int r = smp_update_bond_flag();
    if (r == 0) {
        bt_l2cap_init();
    }
    return r;
}
