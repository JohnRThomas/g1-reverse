#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a6c6 @ 0x0103a6c6
 * public-name: FUN_0103a6c6
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_nrf_rtc_timer_read                     <= FUN_010313a8 @ 0x010313a8
 */
/* net-core FUN_0103a6c6 @ 0x103a6c6  (parity 300 trials PROVEN) */

extern void z_nrf_rtc_timer_read(void);
void FUN_0103a6c6(void)
{
  z_nrf_rtc_timer_read();
}
