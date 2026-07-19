#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086384 @ 0x00086384
 * public-name: delay_scaled_busy_wait
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   delay_busy_wait_usec                     <= FUN_0004c254 @ 0x0004c254
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 */
/* Reconstructed FUN_00086384 @ 0x86384  (parity: 300/300 trials, PROVEN) */

extern void delay_busy_wait_usec(int a);

void delay_scaled_busy_wait(int param_1)
{
  if (param_1 == 0) return;
  delay_busy_wait_usec(param_1);
}
