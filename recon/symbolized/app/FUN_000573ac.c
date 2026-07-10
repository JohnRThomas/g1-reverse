#include "g1_app_symbols.h"
/* named: FUN_000573ac */
/* globals referenced:
//   0x20003a44  free_l2cap_tx_meta_data      
*/
/* Reconstructed FUN_000573ac @ 0x573ac  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(unsigned int, unsigned int, unsigned int);
extern void net_pkt_skip(unsigned int, unsigned int);

void FUN_000573ac(unsigned int param_1)
{
    memset_bytes(param_1, 0, 0x10);
    net_pkt_skip(((uintptr_t)&free_l2cap_tx_meta_data) /*=0x20003a44*/, param_1);
}

