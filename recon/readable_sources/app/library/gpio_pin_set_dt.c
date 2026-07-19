#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c084 @ 0x0007c084
 * public-name: gpio_pin_set_dt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_set_checked                     <= FUN_00017768 @ 0x00017768
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_0007c084 @ 0x7c084 (CFG-directed: 80/80 PASS).
 * Exact out-of-line instance of Zephyr's gpio_pin_set_dt() inline contract.
 */
#include <stdint.h>

struct gpio_dt_spec_recovered {
    const void *port;
    uint8_t pin;
};

extern int gpio_pin_set_checked(const void *port, uint32_t pin, int value);

int gpio_pin_set_dt(const struct gpio_dt_spec_recovered *spec, int value)
{
    return gpio_pin_set_checked(spec->port, spec->pin, value);
}
