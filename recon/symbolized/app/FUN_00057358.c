#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057358 @ 0x00057358
 * public-name: FUN_00057358
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_l2cap_init                            <= FUN_000579d0 @ 0x000579d0
 *   smp_update_bond_flag                     <= FUN_0005e5b8 @ 0x0005e5b8
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   g_bt_conn_tx_pending_cnt                 @ 0x20003a60
 *   g_bt_conn_pool                           @ 0x2000ac7c
 */
/* Reconstructed FUN_00057358 @ 0x57358  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_queue_init(unsigned int);
extern void net_pkt_skip(unsigned int, unsigned int);
extern void FUN_00059690(void);
extern int smp_update_bond_flag(void);
extern void bt_l2cap_init(void);

int FUN_00057358(void)
{
    z_impl_k_queue_init(((unsigned long)&g_bt_conn_tx_pending_cnt) /*=0x20003a60*/);
    unsigned int uVar1 = ((unsigned long)&g_bt_conn_tx_pending_cnt) /*=0x20003a60*/;
    unsigned int iVar3 = ((unsigned long)&g_bt_conn_pool) /*=0x2000ac7c*/;
    int iVar2 = 0;
    do {
        iVar2 = iVar2 + 1;
        net_pkt_skip(uVar1, iVar3);
        iVar3 = iVar3 + 0x10;
    } while (iVar2 != 10);
    FUN_00059690();
    int r = smp_update_bond_flag();
    if (r == 0) {
        bt_l2cap_init();
    }
    return r;
}
