#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007eec0 @ 0x0007eec0
 * public-name: cbvprintf_wrapper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_cbvprintf_impl                         <= FUN_000113a8 @ 0x000113a8
 *   cbvprintf_wrapper                        <= FUN_0007eec0 @ 0x0007eec0
 */
/* Reconstructed FUN_0007eec0 @ 0x7eec0  (parity: 300/300 trials, PROVEN) */

extern void z_cbvprintf_impl(void);
void cbvprintf_wrapper(void)
{
  z_cbvprintf_impl();
  return;
}
