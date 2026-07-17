#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100909c @ 0x0100909c
 * public-name: FUN_0100909c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_0100909c @ 0x100909c  (parity 300 trials PROVEN) */

extern void FUN_0101f764(void);

unsigned int FUN_0100909c(void)
{
  volatile unsigned char *p = (volatile unsigned char *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_0101f764();
    return 0;
  }
  return 0xffffffff;
}
