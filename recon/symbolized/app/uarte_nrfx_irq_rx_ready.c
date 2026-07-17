#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000165b4 @ 0x000165b4
 * public-name: uarte_nrfx_irq_rx_ready
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uarte_nrfx_irq_rx_ready                  <= FUN_000165b4 @ 0x000165b4
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_000165b4 @ 0x165b4  (parity: 300/300 trials, PROVEN) */

int uarte_nrfx_irq_rx_ready(void) {
  int a = *(volatile int*)(((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x64);
  int b = *(volatile int*)0x12345678UL;
  int r = a - b;
  if (r != 0) r = -1;
  return r;
}
