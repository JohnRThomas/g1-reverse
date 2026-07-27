/* readable reconstruction; identity: FUN_00017858 @ 0x00017858
 * public-name: gpio_pin_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_configure                       <= FUN_00017858 @ 0x00017858
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 *   rodata_99e30                             @ 0x00099e30
 *   rodata_99e71                             @ 0x00099e71   [INLINED -- G6 literal batch]
 *   rodata_99e9d                             @ 0x00099e9d   [INLINED -- G6 literal batch]
 *   rodata_99ec7                             @ 0x00099ec7
 *   rodata_99ef2                             @ 0x00099ef2
 *   rodata_99f3c                             @ 0x00099f3c   [INLINED -- G6 literal batch]
 */
/* app-core FUN_00017858 @ 0x00017858 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern void assert_post_action(const void *, unsigned);

typedef void (*pin_config_t)(uintptr_t, unsigned, uint32_t, uint32_t);

void gpio_pin_configure(const uint8_t *pin, uint32_t flags)
{
    uintptr_t dev = *(const uint32_t *)pin;
    unsigned line = pin[4];
    uint32_t mode = flags & 0x600000;
    uint32_t bit;
    volatile uint32_t *enabled;
    volatile uint32_t *output;
    pin_config_t configure;

    if (mode == 0x600000) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)0x99e30, (void *)0x99c53, 0x36a);
        printk((unsigned long)((unsigned long)"\tCannot both enable and disable interrupts\n"));
        assert_post_action((void *)0x99c53, 0x36a);
    } else if (mode == 0) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)((unsigned long)"(flags & ((1U << 21) | (1U << 22))) != 0U"), (void *)0x99c53, 0x36e);
        printk((unsigned long)0x99ec7);
        assert_post_action((void *)0x99c53, 0x36e);
    } else if ((flags & 0x6400000) == 0x400000) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)0x99ef2, (void *)0x99c53, 0x378);
        printk((unsigned long)((unsigned long)"\tAt least one of GPIO_INT_LOW_0, GPIO_INT_HIGH_1 has to be enabled.\n"));
        assert_post_action((void *)0x99c53, 0x378);
    }

    enabled = **(volatile uint32_t ***)(dev + 4);
    configure = *(pin_config_t *)(*(uintptr_t *)(dev + 8) + 0x18);
    output = **(volatile uint32_t ***)(dev + 16);
    bit = 1u << line;
    if ((*enabled & bit) == 0) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U"), (void *)0x99c53, 0x382);
        printk((unsigned long)((unsigned long)"\tUnsupported pin\n"));
        assert_post_action((void *)0x99c53, 0x382);
    }
    if ((flags & 0x800000) && (*output & bit))
        flags ^= 0x6000000;
    configure(dev, line, flags & 0x1600000, flags & 0x6000000);
}
