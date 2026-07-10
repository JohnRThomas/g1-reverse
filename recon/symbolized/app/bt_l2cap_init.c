#include "g1_app_symbols.h"
/* named: bt_l2cap_init */
/* globals referenced:
//   0x20003a44  free_l2cap_tx_meta_data      
//   0x2000ad34  l2cap_tx_meta_data_storage   
*/
/* Reconstructed bt_l2cap_init @ 0x579d0  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_queue_init(int);
extern void net_pkt_skip(int,int);
extern void memset_bytes(int,int,int);
void bt_l2cap_init(void)
{
    z_impl_k_queue_init(((uintptr_t)&free_l2cap_tx_meta_data) /*=0x20003a44*/);
    int uVar1 = ((uintptr_t)&free_l2cap_tx_meta_data) /*=0x20003a44*/;
    int iVar3 = 0;
    int iVar2 = ((uintptr_t)&l2cap_tx_meta_data_storage) /*=0x2000ad34*/;
    do {
        memset_bytes(iVar2, 0, 0x10);
        iVar3 = iVar3 + 1;
        net_pkt_skip(uVar1, iVar2);
        iVar2 = iVar2 + 0x10;
    } while (iVar3 != 10);
}

