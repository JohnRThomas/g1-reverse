#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d7ac @ 0x0100d7ac
 * public-name: FUN_0100d7ac
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_rssi_cal_offset                    @ 0x21000ea6
 */
/* net-core FUN_0100d7ac @ 0x100d7ac  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_0100d7b8 = (volatile unsigned char *)((unsigned long)&g_net_rssi_cal_offset) /*=0x21000ea6*/;
void FUN_0100d7ac(void)
{
  DAT_0100d7b8[0] = 0;
  DAT_0100d7b8[1] = 0;
}
