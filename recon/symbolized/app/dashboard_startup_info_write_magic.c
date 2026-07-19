#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000165a4 @ 0x000165a4
 * public-name: dashboard_startup_info_write_magic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dashboard_startup_info_write_magic       <= FUN_000165a4 @ 0x000165a4
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_000165a4 @ 0x165a4  (parity: 300/300 trials, PROVEN) */

void dashboard_startup_info_write_magic(void)
{
  *(volatile unsigned int *)(((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x64) = 0x12345678UL;
}
