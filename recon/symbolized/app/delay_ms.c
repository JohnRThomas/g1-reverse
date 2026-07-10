#include "g1_app_symbols.h"
/* named: delay_ms */
/* Reconstructed delay_ms @ 0x7d772  (parity: 300/300 trials, PROVEN) */

extern void delay_scaled_busy_wait(int a0);
void delay_ms(int param_1)
{
  delay_scaled_busy_wait(param_1 * 1000);
}

