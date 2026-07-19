#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000851ca @ 0x000851ca
 * public-name: nrf_gpio_cfg_sense_set
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed nrf_gpio_cfg_sense_set @ 0x000851ca from configured NCS 2.5.1 nrf_gpio.h.
 * Identity/backmap: FUN_000851ca.
 */
#include <stdint.h>

extern void gpio_pin_cnf_build_fields(uint32_t pin,
                                      const uint8_t *direction,
                                      const uint8_t *input,
                                      const uint8_t *pull,
                                      const uint8_t *drive,
                                      const uint8_t *sense);
/* gpio_pin_cnf_build_fields <= FUN_00085130 @ 0x00085130 */

void nrf_gpio_cfg_sense_set(uint32_t pin, uint8_t sense)
{
    gpio_pin_cnf_build_fields(pin, 0, 0, 0, 0, &sense);
}
