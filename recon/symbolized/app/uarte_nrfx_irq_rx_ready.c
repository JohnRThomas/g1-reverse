#include "g1_app_symbols.h"
/* named: uarte_nrfx_irq_rx_ready */
/* globals referenced:
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed uarte_nrfx_irq_rx_ready @ 0x165b4  (parity: 300/300 trials, PROVEN) */

int uarte_nrfx_irq_rx_ready(void) {
  int a = *(volatile int*)(((uintptr_t)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x64);
  int b = *(volatile int*)0x12345678UL;
  int r = a - b;
  if (r != 0) r = -1;
  return r;
}

