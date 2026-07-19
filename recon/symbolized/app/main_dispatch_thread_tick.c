#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cb66 @ 0x0007cb66
 * public-name: main_dispatch_thread_tick
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   main_dispatch_thread_tick                <= FUN_0007cb66 @ 0x0007cb66
 */
/* Reconstructed FUN_0007cb66 @ 0x7cb66  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_thread_create(void);

void main_dispatch_thread_tick(void)
{
  z_impl_k_thread_create();
}
