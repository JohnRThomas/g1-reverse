#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010255a4 @ 0x010255a4
 * public-name: FUN_010255a4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010255a4 @ 0x10255a4 CFG_VERIFY_PREFIX_FIRST */

static void DataSynchronizationBarrier(int opt) { (void)opt; }

void FUN_010255a4(void)
{
  volatile unsigned int *p = (volatile unsigned int *)0xe000ed00;
  DataSynchronizationBarrier(0xf);
  p[3] = 0x05fa0004 | (p[3] & 0x700);
  DataSynchronizationBarrier(0xf);
  while (1) { }
}
