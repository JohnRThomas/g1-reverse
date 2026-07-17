/* readable reconstruction; identity: FUN_000179e0 @ 0x000179e0
 * public-name: panel_pwr_gpio_deassert
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   panel_pwr_gpio_deassert                  <= FUN_000179e0 @ 0x000179e0
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 * address symbols (name @ address):
 *   rodata_889f8                             @ 0x000889f8
 */
/* FUN_000179e0 @ 0x179e0: disable the device described at 0x889f8. */

extern void gpio_pin_set_dt(unsigned int descriptor, unsigned int enable,
                         unsigned int arg2, unsigned int arg3);

void panel_pwr_gpio_deassert(unsigned int unused0, unsigned int unused1, unsigned int arg2, unsigned int arg3)
{
    (void)unused0;
    (void)unused1;
    gpio_pin_set_dt(0x000889f8u, 0, arg2, arg3);
}
