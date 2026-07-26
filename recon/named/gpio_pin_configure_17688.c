/* readable reconstruction; identity: FUN_00017688 @ 0x00017688
 * public-name: gpio_pin_configure_17688
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_configure_17688                 <= FUN_00017688 @ 0x00017688
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99c84                             @ 0x00099c84   [INLINED -- G6 literal batch]
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99cda                             @ 0x00099cda   [INLINED -- G6 literal batch]
 *   rodata_99d17                             @ 0x00099d17
 *   rodata_99d5e                             @ 0x00099d5e   [INLINED -- G6 literal batch]
 *   rodata_99dad                             @ 0x00099dad   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 */
/* app-core FUN_00017688 @ 0x00017688 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern void assert_post_action(const void *, unsigned);

void gpio_pin_configure_17688(const uint8_t *pin, uint32_t flags)
{
    uintptr_t dev = *(const uint32_t *)pin;
    uint32_t combined = *(const uint16_t *)(pin + 6) | flags;
    unsigned line = pin[4];
    uint32_t bit;
    volatile uint32_t *enabled;
    volatile uint32_t *output;
    void (**api)(void);

    if ((combined & 0x30) == 0x30) {
        printk((void *)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)((unsigned long)"(flags & ((1 << 4) | (1 << 5))) != ((1 << 4) | (1 << 5))"), (void *)0x99c53, 0x3ca);
        printk((void *)((unsigned long)"\tPull Up and Pull Down should not be enabled simultaneously\n"));
        assert_post_action((void *)0x99c53, 0x3ca);
    } else if ((combined & 0x30002) == 0x10002) {
        printk((void *)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)0x99d17, (void *)0x99c53, 0x3ce);
        printk((void *)((unsigned long)"\tInput cannot be enabled for 'Open Drain', 'Open Source' modes without Output\n"));
        assert_post_action((void *)0x99c53, 0x3ce);
    } else if ((combined & 6) == 4) {
        printk((void *)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)((unsigned long)"(flags & (1 << 1)) != 0 || (flags & (1 << 2)) == 0"), (void *)0x99c53, 0x3d1);
        assert_post_action((void *)0x99c53, 0x3d1);
    }

    enabled = **(volatile uint32_t ***)(dev + 4);
    api = *(void (***)(void))(dev + 8);
    output = **(volatile uint32_t ***)(dev + 16);
    bit = 1u << line;
    if ((*enabled & bit) == 0) {
        printk((void *)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), (void *)((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U"), (void *)0x99c53, 0x3e4);
        printk((void *)((unsigned long)"\tUnsupported pin\n"));
        assert_post_action((void *)0x99c53, 0x3e4);
    }
    if (combined & 1)
        *output |= bit;
    else
        *output &= ~bit;
    (*api)();
}
