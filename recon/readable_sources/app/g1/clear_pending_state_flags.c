#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002ebc8 @ 0x0002ebc8
 * public-name: clear_pending_state_flags
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_pending_state_flags                <= FUN_0002ebc8 @ 0x0002ebc8
 * address symbols (name @ address):
 *   g_ancs_inbox_flag_current                @ 0x20018da6
 *   g_lid_closed_flag                        @ 0x20018da7
 *   g_charging_flag                          @ 0x20018da8
 */
/* Reconstructed FUN_0002ebc8 @ 0x2ebc8  (parity: 300/300 trials, PROVEN) */

void clear_pending_state_flags(void)
{
  *(volatile unsigned char *)((unsigned long)&g_ancs_inbox_flag_current) /*=0x20018da6*/ = 0;
  *(volatile unsigned char *)((unsigned long)&g_lid_closed_flag) /*=0x20018da7*/ = 0;
  *(volatile unsigned char *)((unsigned long)&g_charging_flag) /*=0x20018da8*/ = 0;
}
