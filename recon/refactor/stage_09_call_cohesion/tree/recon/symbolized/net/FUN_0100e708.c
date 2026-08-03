#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e708 @ 0x0100e708
 * public-name: FUN_0100e708
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e708 @ 0x100e708  (parity 300 trials PROVEN) */

void FUN_0100e708(int param_1, unsigned int *param_2)
{
  *(unsigned int *)(param_1 + 4) = *param_2;
  *(unsigned char *)(param_1 + 8) = *((unsigned char *)param_2 + 4);
}
