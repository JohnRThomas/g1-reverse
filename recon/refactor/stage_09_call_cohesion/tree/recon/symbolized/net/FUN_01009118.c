#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01009118 @ 0x01009118
 * public-name: FUN_01009118
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_01009118 @ 0x1009118  (parity 300 trials PROVEN) */

extern void FUN_0101f680(void);

unsigned int FUN_01009118(void)
{
  volatile unsigned char *p = (volatile unsigned char *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_0101f680();
    return 0;
  }
  return 0xffffffff;
}
