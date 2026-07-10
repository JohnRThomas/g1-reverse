#include "g1_app_symbols.h"
/* named: gpio_dt_spec_activate */
/* Reconstructed gpio_dt_spec_activate @ 0x179ec  (parity: 300/300 trials, PROVEN) */

extern void gpio_pin_set_checked(unsigned char, unsigned char, unsigned int);
void gpio_dt_spec_activate(void)
{
  gpio_pin_set_checked(*(volatile unsigned char *)((uintptr_t)&tbl_889d0) /*=0x889f8*/, *(volatile unsigned char *)((uintptr_t)&tbl_889d0) /*=0x889f9*/, 1);
}

