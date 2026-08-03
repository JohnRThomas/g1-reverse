#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f73c @ 0x0101f73c
 * public-name: FUN_0101f73c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_intrusive_list_append_unique  <= FUN_010294d2 @ 0x010294d2
 */
/* net-core FUN_0101f73c @ 0x101f73c  (parity 300 trials PROVEN) */

extern void controller_intrusive_list_append_unique(unsigned int a, unsigned int b);

void FUN_0101f73c(void)
{
  controller_intrusive_list_append_unique(G1N_21001230 + 0x20c, G1N_210004e0);
  controller_intrusive_list_append_unique(G1N_21001230 + 0x210, G1N_210004e8);
}
