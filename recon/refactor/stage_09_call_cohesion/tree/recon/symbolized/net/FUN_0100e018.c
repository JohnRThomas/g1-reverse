#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e018 @ 0x0100e018
 * public-name: FUN_0100e018
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e018 @ 0x100e018  (parity 300 trials PROVEN) */

void FUN_0100e018(char *param_1, unsigned int *param_2)
{
  unsigned int v = *(unsigned int *)(param_1 + 3);
  param_2[0] = v;
  unsigned short h = *(unsigned short *)(param_1 + 7);
  *(unsigned short *)((char*)param_2 + 4) = h;
}
