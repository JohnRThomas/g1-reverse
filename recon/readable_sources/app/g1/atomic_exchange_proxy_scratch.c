#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002f910 @ 0x0002f910
 * public-name: atomic_exchange_proxy_scratch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_exchange_proxy_scratch            <= FUN_0002f910 @ 0x0002f910
 * address symbols (name @ address):
 *   g_atomic_scratch_20007bb0                @ 0x20007bb0
 */
/* Reconstructed FUN_0002f910 @ 0x2f910  (parity: 300/300 trials, PROVEN) */

unsigned int atomic_exchange_proxy_scratch(unsigned int param_1)
{
  volatile unsigned int *p = (volatile unsigned int *)((unsigned long)&g_atomic_scratch_20007bb0) /*=0x20007bb0*/;
  unsigned int old = *p;
  *p = param_1;
  return old;
}
