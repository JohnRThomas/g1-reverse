#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010126f0 @ 0x010126f0
 * public-name: FUN_010126f0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010126f0 @ 0x10126f0  (parity 300 trials PROVEN) */

unsigned int FUN_010126f0(char *param_1)
{
  return *(unsigned short *)(param_1 + 2) == 9;
}
