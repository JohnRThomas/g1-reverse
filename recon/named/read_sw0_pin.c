/* named: read_sw0_pin */
/* globals referenced:
//   0x00087b48  g_gpio1_dev                  
*/
/* Reconstructed read_sw0_pin @ 0x17e30  (parity: 300/300 trials, PROVEN) */

extern void gpio_pin_get_raw_checked(unsigned int a, unsigned int b);
void read_sw0_pin(void)
{
    gpio_pin_get_raw_checked(0x87b48UL, 9);
}

