/* readable reconstruction; identity: FUN_00066e70 @ 0x00066e70
 * public-name: pin_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_port_base_get               <= FUN_00066d1c @ 0x00066d1c
 *   pin_init                                 <= FUN_00066e70 @ 0x00066e70
 *   nrf_gpio_pin_outset                      <= FUN_000852e6 @ 0x000852e6
 *   nrf_gpio_pin_set                         <= FUN_000852fe @ 0x000852fe
 */
/* Reconstructed pin_init @ 0x00066e70 (FUN_00066e70; CFG-verified). */
/* Pinned nrfx_spim.c static helper; raw public identity retained for backmapping. */
#include <stdint.h>
extern uintptr_t nrf_gpio_pin_port_base_get(uint32_t *descriptor);
extern void nrf_gpio_pin_outset(uint32_t pin);
extern void nrf_gpio_pin_set(uint32_t pin);
void pin_init(uint32_t pin, uint32_t output, uint32_t pull,
                  uint32_t drive, uint32_t initial_state)
{
    if (pin == UINT32_MAX) return;
    if (output == 1u) {
        if (initial_state != 0u) nrf_gpio_pin_outset(pin);
        else nrf_gpio_pin_set(pin);
    }
    uint32_t descriptor = pin;
    uintptr_t port = nrf_gpio_pin_port_base_get(&descriptor);
    volatile uint32_t *cnf = (volatile uint32_t *)(port + descriptor * 4u + 0x200u);
    *cnf = (*cnf & 0xfffcf0f0u) | (drive << 8) | (pull << 2) |
           output | (output << 1);
}
