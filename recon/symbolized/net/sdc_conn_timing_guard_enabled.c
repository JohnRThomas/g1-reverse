#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01016160 @ 0x01016160
 * public-name: sdc_conn_timing_guard_enabled
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_conn_timing_guard_enabled            <= FUN_01016160 @ 0x01016160
 * address symbols (name @ address):
 *   g_net_link_ctx_a                         @ 0x21000f68
 */
/* net-core FUN_01016160 @ 0x1016160  (parity 300 trials PROVEN) */

static volatile int * const DAT_0101616c = (volatile int *)((unsigned long)&g_net_link_ctx_a) /*=0x21000f68*/;
int sdc_conn_timing_guard_enabled(void)
{
  int v = DAT_0101616c[2];
  if (v != 0) v = 1;
  return v;
}
