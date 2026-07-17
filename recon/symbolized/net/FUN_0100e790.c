#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e790 @ 0x0100e790
 * public-name: FUN_0100e790
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e790 @ 0x100e790  (parity 300 trials PROVEN) */

void FUN_0100e790(int param_1, unsigned int *param_2)
{
  unsigned int uVar1 = *(unsigned int *)(param_1 + 8);
  *param_2 = *(unsigned int *)(param_1 + 4);
  param_2[1] = uVar1;
}
