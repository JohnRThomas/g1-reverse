#include "g1_app_symbols.h"
/* named: rtc_get_elapsed_cycles_since_baseline */
/* globals referenced:
//   0x2000b494  g_rtc_elapsed_calc_disabled_flag 
*/
/* Reconstructed rtc_get_elapsed_cycles_since_baseline @ 0x74b68  (parity: 300/300 trials, PROVEN) */

extern int rtc_read_extended_cycle_count(void);
int rtc_get_elapsed_cycles_since_baseline(void)
{
  if (*(volatile unsigned int *)((uintptr_t)&g_rtc_elapsed_calc_disabled_flag) /*=0x2000b494*/ == 0) {
    return rtc_read_extended_cycle_count();
  }
  return 0;
}

