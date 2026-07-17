/* readable reconstruction; identity: FUN_000527dc @ 0x000527dc
 * public-name: FUN_000527dc
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_active_transfer_conn                   @ 0x20005cb0
 */
/* Reconstructed FUN_000527dc @ 0x527dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int* FUN_000527dc(int param_1)
{
  volatile int *p = (volatile int*)0x20005cb0UL;
  if (*p != param_1) {
    return (int*)0;
  }
  return (int*)p;
}
