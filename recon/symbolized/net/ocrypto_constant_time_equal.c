#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01008810 @ 0x01008810
 * public-name: ocrypto_constant_time_equal
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ocrypto_constant_time_equal              <= FUN_01008810 @ 0x01008810
 */
/* net-core FUN_01008810 @ 0x1008810  (parity 300 trials PROVEN) */

unsigned int ocrypto_constant_time_equal(unsigned char *param_1, unsigned char *param_2, int param_3)
{
  unsigned int uVar1;

  uVar1 = 0;
  do {
    param_3 = param_3 - 1;
    uVar1 = uVar1 | (*param_1 ^ *param_2);
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while (param_3 != 0);
  return (uVar1 - 1) >> 0x1f;
}
