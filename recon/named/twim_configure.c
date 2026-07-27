/* readable reconstruction; identity: FUN_000675c0 @ 0x000675c0
 * public-name: twim_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_enable                          <= FUN_000500ac @ 0x000500ac
 * address symbols (name @ address):
 *   g_nrfx_twim_cb                           @ 0x2000b3cc
 */
/* Reconstructed nrfx_twim twim_configure @ 0x000675c0.
 * Raw/address back-map: FUN_000675c0 / 0x000675c0.
 */
#include <stdint.h>

struct nrfx_twim_instance_raw {
    volatile uint8_t *peripheral;
    uint8_t driver_index;
};

struct nrfx_twim_config_raw {
    uint32_t scl_pin;
    uint32_t sda_pin;
    uint32_t frequency;
    uint8_t interrupt_priority;
    uint8_t hold_bus_uninit;
    uint8_t reserved;
    uint8_t skip_psel_cfg;
};

extern void arch_irq_enable(unsigned int);

void twim_configure(const struct nrfx_twim_instance_raw *instance,
                    const struct nrfx_twim_config_raw *config)
{
    volatile uint8_t *peripheral = instance->peripheral;

    if (config->skip_psel_cfg == 0u) {
        *(volatile uint32_t *)(peripheral + 0x508) = config->scl_pin;
        *(volatile uint32_t *)(peripheral + 0x50c) = config->sda_pin;
    }
    *(volatile uint32_t *)(peripheral + 0x524) = config->frequency;

    volatile uint32_t *handlers = (volatile uint32_t *)0x2000b3ccu;
    if (handlers[(uint32_t)instance->driver_index * 10u] != 0u) {
        arch_irq_enable(((uint32_t)(uintptr_t)peripheral >> 12) & 0xffu);
    }
}
