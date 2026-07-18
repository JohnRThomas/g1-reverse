#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000579d0 @ 0x000579d0
 * public-name: bt_l2cap_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_l2cap_init                            <= FUN_000579d0 @ 0x000579d0
 *   g1_recon_z_impl_k_queue_init             <= FUN_000864e8 @ 0x000864e8
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   free_l2cap_tx_meta_data                  @ 0x20003a44
 *   l2cap_tx_meta_data_storage               @ 0x2000ad34
 */
/* Reconstructed FUN_000579d0 @ 0x579d0  (parity: 300/300 trials, PROVEN) */

#define g1_recon_z_impl_k_queue_init g1_recon_z_impl_k_queue_init
extern void g1_recon_z_impl_k_queue_init(void *queue);
extern void net_pkt_skip(int,int);
extern void memset_bytes(int,int,int);
void bt_l2cap_init(void)
{
    g1_recon_z_impl_k_queue_init((void *)((unsigned long)&free_l2cap_tx_meta_data) /*=0x20003a44*/);
    int uVar1 = ((unsigned long)&free_l2cap_tx_meta_data) /*=0x20003a44*/;
    int iVar3 = 0;
    int iVar2 = ((unsigned long)&l2cap_tx_meta_data_storage) /*=0x2000ad34*/;
    do {
        memset_bytes(iVar2, 0, 0x10);
        iVar3 = iVar3 + 1;
        net_pkt_skip(uVar1, iVar2);
        iVar2 = iVar2 + 0x10;
    } while (iVar3 != 10);
}
