#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e054 @ 0x0100e054
 * public-name: FUN_0100e054
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e054 @ 0x100e054  (parity 300 trials PROVEN) */

void FUN_0100e054(unsigned char *param_1, unsigned int param_2)
{
  unsigned int v = (*param_1 & 0x7f) | (param_2 << 7);
  *param_1 = (unsigned char)v;
}
