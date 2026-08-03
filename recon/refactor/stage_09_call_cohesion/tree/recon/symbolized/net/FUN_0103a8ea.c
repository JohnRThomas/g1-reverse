#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a8ea @ 0x0103a8ea
 * public-name: FUN_0103a8ea
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a8ea @ 0x103a8ea  (parity 300 trials PROVEN) */

unsigned int FUN_0103a8ea(unsigned int param_1)
{
  unsigned int uVar1;

  if ((param_1 >> 5) == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    if ((param_1 >> 5) != 1) {
      return 0;
    }
    uVar1 = 0xffff;
  }
  return (uVar1 >> (param_1 & 0x1f)) & 1;
}
