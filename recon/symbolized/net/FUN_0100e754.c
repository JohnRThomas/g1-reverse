#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e754 @ 0x0100e754
 * public-name: FUN_0100e754
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e754 @ 0x100e754  (parity 300 trials PROVEN) */

void FUN_0100e754(char *param_1, unsigned int *param_2)
{
  unsigned int v2 = param_2[1];
  *(unsigned int *)(param_1 + 0xe) = param_2[0];
  *(unsigned int *)(param_1 + 0x12) = v2;
}
