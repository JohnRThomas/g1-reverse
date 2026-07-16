/* Full reconstruction FUN_00061f64 @ 0x00061f64 (72-byte exact extent). */
#include <stdint.h>

extern void FUN_0007e2fa(uintptr_t, uintptr_t, uintptr_t, uint32_t);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));

uintptr_t FUN_00061f64(uint32_t *encoded_pin)
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
        FUN_0007e2fa(0x00099cbdu, 0x000f0a04u, 0x000f09d1u, 0x32fu);
        FUN_0007e2ec(0x000f09d1u, 0x32fu);
    }
    *encoded_pin = pin;
    return gpio;
}
