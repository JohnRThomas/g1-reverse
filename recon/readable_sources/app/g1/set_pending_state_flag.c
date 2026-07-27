#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002eb28 @ 0x0002eb28
 * public-name: set_pending_state_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_pending_state_flag                   <= FUN_0002eb28 @ 0x0002eb28
 * address symbols (name @ address):
 *   g_ancs_inbox_flag_current                @ 0x20018da6
 */
/* Reconstructed FUN_0002eb28 @ 0x2eb28  (parity: 300/300 trials, PROVEN) */

void set_pending_state_flag(unsigned long param_1, unsigned long param_2) {
  if (param_1 < 3) {
    if (param_2 != 0) {
      *(volatile unsigned char *)(((unsigned long)&g_ancs_inbox_flag_current) /*=0x20018da6*/ + param_1) = 1;
      return;
    }
    *(volatile unsigned char *)(((unsigned long)&g_ancs_inbox_flag_current) /*=0x20018da6*/ + param_1) = 0;
  }
}
