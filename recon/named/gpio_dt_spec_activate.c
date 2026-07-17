/* readable reconstruction; identity: FUN_000179ec @ 0x000179ec
 * public-name: gpio_dt_spec_activate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_dt_spec_activate                    <= FUN_000179ec @ 0x000179ec
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 * address symbols (name @ address):
 *   rodata_889f8                             @ 0x000889f8
 */
/* Reconstructed FUN_000179ec @ 0x179ec  (parity: 300/300 trials, PROVEN) */

extern void gpio_pin_set_dt(unsigned int, unsigned int, unsigned int, unsigned int);

void gpio_dt_spec_activate(unsigned int unused0, unsigned int unused1,
                  unsigned int arg2, unsigned int arg3)
{
  (void)unused0;
  (void)unused1;
  gpio_pin_set_dt(0x000889f8U, 1, arg2, arg3);
}
