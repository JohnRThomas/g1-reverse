#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101f764 @ 0x0101f764
 * public-name: FUN_0101f764
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101f764 @ 0x101f764  (parity 300 trials PROVEN) */

extern void FUN_010294d2(unsigned int, unsigned int);

void FUN_0101f764(void)
{
  unsigned int base = 0x21001230;

  FUN_010294d2(base + 0x20c, 0x21000518);
  FUN_010294d2(base + 0x210, 0x21000520);
  FUN_010294d2(base + 0x214, 0x21000510);
}
