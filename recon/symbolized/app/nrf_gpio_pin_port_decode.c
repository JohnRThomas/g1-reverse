#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00061f64 @ 0x00061f64
 * public-name: nrf_gpio_pin_port_decode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_port_decode                 <= FUN_00061f64 @ 0x00061f64
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f09d1                             @ 0x000f09d1
 *   rodata_f0a04                             @ 0x000f0a04
 */
/* Full reconstruction FUN_00061f64 @ 0x00061f64 (72-byte exact extent). */
#include <stdint.h>

extern void printk(uintptr_t, uintptr_t, uintptr_t, uint32_t);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));

uintptr_t nrf_gpio_pin_port_decode(uint32_t *encoded_pin)
{
    uint32_t pin = *encoded_pin;
    uint32_t bank = pin >> 5;
    uintptr_t gpio;

    if (bank == 0) {
        if (((0xffffffffu >> (pin & 31u)) & 1u) == 0)
            goto invalid;
        gpio = 0x50842500u;
    } else if (bank == 1) {
        pin &= 31u;
        if (((0xffffu >> pin) & 1u) == 0)
            goto invalid;
        gpio = 0x50842800u;
    } else {
invalid:
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0a04) /*=0xf0a04*/, ((unsigned long)&rodata_f09d1) /*=0xf09d1*/, 0x32fu);
        assert_post_action(((unsigned long)&rodata_f09d1) /*=0xf09d1*/, 0x32fu);
    }
    *encoded_pin = pin;
    return gpio;
}
