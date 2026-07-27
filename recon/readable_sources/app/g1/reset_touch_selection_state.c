#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00037098 @ 0x00037098
 * public-name: reset_touch_selection_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_startup_default_language   <= FUN_0001672c @ 0x0001672c
 *   reset_touch_selection_state              <= FUN_00037098 @ 0x00037098
 * address symbols (name @ address):
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_widget0_index_raw                      @ 0x2001b816
 */
/* Reconstructed FUN_00037098 @ 0x37098  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void set_dashboard_startup_default_language(unsigned char);
void reset_touch_selection_state(void)
{
  *(volatile uint8_t*)(((unsigned long)&g_dashboard_widget_state) /*=0x20004950*/ + 1) = 0;
  *(volatile uint8_t*)((unsigned long)&g_widget0_index_raw) /*=0x2001b816*/ = 0;
  set_dashboard_startup_default_language(0);
  return;
}
