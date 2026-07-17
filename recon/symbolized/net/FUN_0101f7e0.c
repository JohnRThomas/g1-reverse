#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f7e0 @ 0x0101f7e0
 * public-name: FUN_0101f7e0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101f7e0 @ 0x101f7e0  (parity 300 trials PROVEN) */

extern void FUN_010294d2(unsigned int, unsigned int);

void FUN_0101f7e0(void)
{
  unsigned int base = 0x21001230;

  FUN_010294d2(base + 0x20c, 0x210004f0);
  FUN_010294d2(base + 0x210, 0x21000508);
  FUN_010294d2(base + 0x214, 0x210004f8);
}
