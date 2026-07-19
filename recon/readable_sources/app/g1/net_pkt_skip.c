#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086502 @ 0x00086502
 * public-name: net_pkt_skip
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_queue_insert_and_wake                  <= FUN_00072674 @ 0x00072674
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 */
/* Reconstructed FUN_00086502 @ 0x86502  (parity: 300/300 trials, PROVEN) */

extern void k_queue_insert_and_wake(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void net_pkt_skip(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    k_queue_insert_and_wake(param_1, 0, param_2, 0, 1, param_2, param_3);
}
