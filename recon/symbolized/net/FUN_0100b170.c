#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100b170 @ 0x0100b170
 * public-name: FUN_0100b170
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 */
/* net-core FUN_0100b170 @ 0x100b170  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_0100b17c = (volatile unsigned char *)((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/;
void FUN_0100b170(void)
{
  DAT_0100b17c[0x3c] = 1;
}
