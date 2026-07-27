/* readable reconstruction; identity: FUN_00017e30 @ 0x00017e30
 * public-name: read_sw0_pin
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_get_raw_checked                 <= FUN_000177c4 @ 0x000177c4
 *   read_sw0_pin                             <= FUN_00017e30 @ 0x00017e30
 * address symbols (name @ address):
 *   g_gpio1_dev                              @ 0x00087b48
 */
/* Reconstructed FUN_00017e30 @ 0x17e30  (parity: 300/300 trials, PROVEN) */

extern int gpio_pin_get_raw_checked(char*, unsigned int);
void read_sw0_pin(void)
{
    gpio_pin_get_raw_checked(0x87b48UL, 9);
}
