#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086502 @ 0x00086502
 * public-name: net_pkt_skip
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 */
/* Reconstructed FUN_00086502 @ 0x86502  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072674(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void net_pkt_skip(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    FUN_00072674(param_1, 0, param_2, 0, 1, param_2, param_3);
}
