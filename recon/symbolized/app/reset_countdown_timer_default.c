#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d1b8 @ 0x0007d1b8
 * public-name: reset_countdown_timer_default
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   reset_countdown_timer_default            <= FUN_0007d1b8 @ 0x0007d1b8
 */
/* Reconstructed FUN_0007d1b8 @ 0x7d1b8  (parity: 300/300 trials, PROVEN) */

void reset_countdown_timer_default(unsigned char *param_1) {
  param_1[1] = 0;
  param_1[0] = 0x3c;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
}
