#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0001658c @ 0x0001658c
 * public-name: FUN_0001658c
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_0001658c @ 0x1658c  (parity: 300/300 trials, PROVEN) */

void FUN_0001658c(unsigned char param_1)
{
  *(volatile unsigned char *)(((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x63) = param_1;
}
