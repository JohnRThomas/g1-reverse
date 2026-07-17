#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036128 @ 0x01036128
 * public-name: FUN_01036128
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01036128 @ 0x1036128  (parity 300 trials PROVEN) */

int FUN_01036128(unsigned int *param_1) {
  volatile unsigned char *base = (volatile unsigned char *)0x21004b28;
  unsigned int v = *(volatile unsigned int *)(0x21004b28 + 8) | (unsigned int)base[0x10];
  int bVar1 = (*param_1 == v);
  if (bVar1) *param_1 = 0;
  return bVar1;
}
