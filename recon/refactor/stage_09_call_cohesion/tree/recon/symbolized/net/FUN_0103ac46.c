#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103ac46 @ 0x0103ac46
 * public-name: FUN_0103ac46
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103ac46 @ 0x103ac46  (parity 300 trials PROVEN) */

unsigned int FUN_0103ac46(int param_1, int param_2)
{
  return *(unsigned int *)(*(int *)(param_1 + 0x18) + param_2 * 0x10 + 8);
}
