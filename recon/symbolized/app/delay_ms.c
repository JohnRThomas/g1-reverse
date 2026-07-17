#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d772 @ 0x0007d772
 * public-name: delay_ms
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 */
/* Reconstructed FUN_0007d772 @ 0x7d772  (parity: 300/300 trials, PROVEN) */

extern void delay_scaled_busy_wait(int a0);
void delay_ms(int param_1)
{
  delay_scaled_busy_wait(param_1 * 1000);
}
