#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010122a8 @ 0x010122a8
 * public-name: FUN_010122a8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010122a8 @ 0x10122a8  (parity 300 trials PROVEN) */

int FUN_010122a8(unsigned char *param_1)
{
  int iVar1 = (int)(*param_1) - 0xff;
  if (iVar1 != 0) {
    iVar1 = 1;
  }
  return iVar1;
}
