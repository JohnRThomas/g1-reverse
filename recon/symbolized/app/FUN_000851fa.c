#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000851fa @ 0x000851fa
 * public-name: FUN_000851fa
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_configure_pin_output                <= FUN_0006666c @ 0x0006666c
 */
/* Reconstructed FUN_000851fa @ 0x851fa  (parity: 300/300 trials, PROVEN) */

extern void gpio_configure_pin_output(unsigned int param_1, unsigned int param_2);
void FUN_000851fa(unsigned int param_1)
{
    gpio_configure_pin_output(param_1, 0);
}
