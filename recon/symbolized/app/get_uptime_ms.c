#include "g1_app_symbols.h"
/* named: get_uptime_ms */
/* Reconstructed get_uptime_ms @ 0x86690  (parity: 300/300 trials, PROVEN) */

extern void k_uptime_ticks_impl(void);
void get_uptime_ms(void)
{
  k_uptime_ticks_impl();
}

