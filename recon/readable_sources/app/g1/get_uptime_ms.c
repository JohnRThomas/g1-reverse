#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086690 @ 0x00086690
 * public-name: get_uptime_ms
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_uptime_ticks_impl                      <= FUN_00074f68 @ 0x00074f68
 *   get_uptime_ms                            <= FUN_00086690 @ 0x00086690
 */
/* Reconstructed FUN_00086690 @ 0x86690  (parity: 300/300 trials, PROVEN) */

extern void k_uptime_ticks_impl(void);
void get_uptime_ms(void)
{
  k_uptime_ticks_impl();
}
