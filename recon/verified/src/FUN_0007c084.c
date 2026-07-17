/* Reconstructed FUN_0007c084 @ 0x7c084 (CFG-directed: 80/80 PASS).
 * Exact out-of-line instance of Zephyr's gpio_pin_set_dt() inline contract.
 */
#include <stdint.h>

struct gpio_dt_spec_recovered {
    const void *port;
    uint8_t pin;
};

extern int FUN_00017768(const void *port, uint32_t pin, int value);

int FUN_0007c084(const struct gpio_dt_spec_recovered *spec, int value)
{
    return FUN_00017768(spec->port, spec->pin, value);
}
