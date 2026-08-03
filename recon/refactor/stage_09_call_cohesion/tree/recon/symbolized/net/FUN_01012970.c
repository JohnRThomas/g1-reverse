#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01012970 @ 0x01012970
 * public-name: FUN_01012970
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01012970 @ 0x1012970  (parity 300 trials PROVEN) */

void FUN_01012970(int param_1, unsigned char param_2, unsigned char param_3)
{
  *(unsigned char *)(param_1 + 0x20) = param_2;
  *(unsigned char *)(param_1 + 0x21) = param_3;
}
