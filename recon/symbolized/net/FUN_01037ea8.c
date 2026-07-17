#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037ea8 @ 0x01037ea8
 * public-name: FUN_01037ea8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01037ea8 @ 0x1037ea8  (parity 300 trials PROVEN) */

extern void FUN_010375b8(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6);

void FUN_01037ea8(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int *p7)
{
  FUN_010375b8(p1, p2, p3, p4, p5, p6);
  if (p7 != 0) {
    volatile unsigned char *base = (volatile unsigned char *)0x21004b28;
    unsigned int step1 = *(unsigned int *)(base + 8);
    *p7 = *(unsigned int *)((unsigned char *)step1 + 0x14);
  }
  return;
}
