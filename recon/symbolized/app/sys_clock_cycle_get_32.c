#include "g1_app_symbols.h"
/* named: sys_clock_cycle_get_32 */
/* Reconstructed sys_clock_cycle_get_32 @ 0x84c76  (parity: 300/300 trials, PROVEN) */

extern void rtc_read_extended_cycle_count(void);
void sys_clock_cycle_get_32(void)
{
    rtc_read_extended_cycle_count();
}

