#include "g1_app_symbols.h"
/* named: clear_pending_state_flags */
/* globals referenced:
//   0x20018da6  g_ancs_inbox_flag_current    
*/
/* Reconstructed clear_pending_state_flags @ 0x2ebc8  (parity: 300/300 trials, PROVEN) */

void clear_pending_state_flags(void)
{
  *(volatile unsigned char *)((uintptr_t)&g_ancs_inbox_flag_current) /*=0x20018da6*/ = 0;
  *(volatile unsigned char *)((uintptr_t)&g_lid_closed_flag) /*=0x20018da7*/ = 0;
  *(volatile unsigned char *)((uintptr_t)&g_charging_flag) /*=0x20018da8*/ = 0;
}

