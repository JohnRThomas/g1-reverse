#include "g1_app_symbols.h"
/* named: FUN_000851fa */
/* Reconstructed FUN_000851fa @ 0x851fa  (parity: 300/300 trials, PROVEN) */

extern void gpio_configure_pin_output(unsigned int param_1, unsigned int param_2);
void FUN_000851fa(unsigned int param_1)
{
    gpio_configure_pin_output(param_1, 0);
}

