#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000573ac @ 0x000573ac
 * public-name: l2cap_tx_meta_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_tx_meta_free                       <= FUN_000573ac @ 0x000573ac
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   free_l2cap_tx_meta_data                  @ 0x20003a44
 */
/* Reconstructed FUN_000573ac @ 0x573ac  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern void net_pkt_skip(unsigned int, unsigned int);

void l2cap_tx_meta_free(unsigned int param_1)
{
    memset_bytes(param_1, 0, 0x10);
    net_pkt_skip(((unsigned long)&free_l2cap_tx_meta_data) /*=0x20003a44*/, param_1);
}
