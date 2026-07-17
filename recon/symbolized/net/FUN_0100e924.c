#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e924 @ 0x0100e924
 * public-name: FUN_0100e924
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 */
/* net-core FUN_0100e924 @ 0x100e924  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_0100e930 = (volatile unsigned char *)((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
unsigned char FUN_0100e924(void)
{
  return (unsigned char)((~DAT_0100e930[0x16]) & 1);
}
