/* named: panel_pwr_gpio_deassert */
/* Reconstructed panel_pwr_gpio_deassert @ 0x179e0  (parity: 300/300 trials, PROVEN) */

extern void gpio_pin_set_checked(unsigned int a, unsigned char b, unsigned int c);
void panel_pwr_gpio_deassert(void)
{
    gpio_pin_set_checked(*(volatile unsigned int*)0x889f8UL, *(volatile unsigned char*)0x889f9UL, 0);
}

