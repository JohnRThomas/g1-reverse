#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_gpio_pin_desc__param_0028              [param_0028; G1-original]
 * Raw function identity: 0x00017688.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00017688 @ 0x00017688
 * public-name: gpio_pin_configure_17688
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_configure_17688                 <= FUN_00017688 @ 0x00017688
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99c84                             @ 0x00099c84
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_99cda                             @ 0x00099cda
 *   rodata_99d17                             @ 0x00099d17
 *   rodata_99d5e                             @ 0x00099d5e
 *   rodata_99dad                             @ 0x00099dad
 *   rodata_99de0                             @ 0x00099de0
 *   rodata_99e1e                             @ 0x00099e1e
 */
/* app-core FUN_00017688 @ 0x00017688 */
#include <stdint.h>

extern void printk(const void *, ...);
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
        printk((void *)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void *)((unsigned long)&rodata_99c84) /*=0x99c84*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ca);
        printk((void *)((unsigned long)&rodata_99cda) /*=0x99cda*/);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ca);
    } else if ((combined & 0x30002) == 0x10002) {
        printk((void *)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void *)((unsigned long)&rodata_99d17) /*=0x99d17*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ce);
        printk((void *)((unsigned long)&rodata_99d5e) /*=0x99d5e*/);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ce);
    } else if ((combined & 6) == 4) {
        printk((void *)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void *)((unsigned long)&rodata_99dad) /*=0x99dad*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3d1);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3d1);
    }

    enabled = **(volatile uint32_t ***)(dev + 4);
    api = *(void (***)(void))(dev + 8);
    output = **(volatile uint32_t ***)(dev + 16);
    bit = 1u << line;
    if ((*enabled & bit) == 0) {
        printk((void *)((unsigned long)&rodata_99cbd) /*=0x99cbd*/, (void *)((unsigned long)&rodata_99de0) /*=0x99de0*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3e4);
        printk((void *)((unsigned long)&rodata_99e1e) /*=0x99e1e*/);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3e4);
    }
    if (combined & 1)
        *output |= bit;
    else
        *output &= ~bit;
    (*api)();
}
