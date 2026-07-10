#include "g1_app_symbols.h"
/* named: set_dashboard_startup_default_language */
/* globals referenced:
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed set_dashboard_startup_default_language @ 0x1672c  (parity: 300/300 trials, PROVEN) */

void set_dashboard_startup_default_language(unsigned char param_1)
{
  *(volatile unsigned char *)(((uintptr_t)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x69) = param_1;
}

