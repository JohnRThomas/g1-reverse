/* named: gpio_dt_spec_activate */
/* Reconstructed gpio_dt_spec_activate @ 0x179ec  (parity: 300/300 trials, PROVEN) */

extern void gpio_pin_set_checked(unsigned char, unsigned char, unsigned int);
void gpio_dt_spec_activate(void)
{
  gpio_pin_set_checked(*(volatile unsigned char *)0x889f8UL, *(volatile unsigned char *)0x889f9UL, 1);
}

