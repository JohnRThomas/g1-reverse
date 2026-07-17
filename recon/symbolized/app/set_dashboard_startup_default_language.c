#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0001672c @ 0x0001672c
 * public-name: set_dashboard_startup_default_language
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_startup_default_language   <= FUN_0001672c @ 0x0001672c
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_0001672c @ 0x1672c  (parity: 300/300 trials, PROVEN) */

void set_dashboard_startup_default_language(unsigned char param_1)
{
  *(volatile unsigned char *)(((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x69) = param_1;
}
