/* readable reconstruction; identity: FUN_000851fa @ 0x000851fa
 * public-name: nrf_gpio_cfg_default
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_configure_pin_output                <= FUN_0006666c @ 0x0006666c
 *   nrf_gpio_cfg_default                     <= FUN_000851fa @ 0x000851fa
 */
/* Reconstructed FUN_000851fa @ 0x851fa  (parity: 300/300 trials, PROVEN) */

extern void gpio_configure_pin_output(unsigned int param_1, unsigned int param_2);
void nrf_gpio_cfg_default(unsigned int param_1)
{
    gpio_configure_pin_output(param_1, 0);
}
