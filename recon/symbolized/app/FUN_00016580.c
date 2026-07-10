#include "g1_app_symbols.h"
/* named: FUN_00016580 */
/* globals referenced:
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed FUN_00016580 @ 0x16580  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00016580(void)
{
  return *(volatile unsigned char *)(((uintptr_t)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 0x63);
}

