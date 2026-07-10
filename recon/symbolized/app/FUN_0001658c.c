#include "g1_app_symbols.h"
/* named: FUN_0001658c */
/* globals referenced:
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed FUN_0001658c @ 0x1658c  (parity: 300/300 trials, PROVEN) */

void FUN_0001658c(unsigned char param_1)
{
  *(volatile unsigned char *)(((uintptr_t)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x63) = param_1;
}

