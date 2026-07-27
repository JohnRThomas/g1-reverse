/* app-core FUN_00017858 @ 0x00017858 */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(const void *, unsigned);

typedef void (*pin_config_t)(uintptr_t, unsigned, uint32_t, uint32_t);

void FUN_00017858(const uint8_t *pin, uint32_t flags)
{
    uintptr_t dev = *(const uint32_t *)pin;
    unsigned line = pin[4];
    uint32_t mode = flags & 0x600000;
    uint32_t bit;
    volatile uint32_t *enabled;
    volatile uint32_t *output;
    pin_config_t configure;

    if (mode == 0x600000) {
        FUN_0007e2fa((unsigned long)0x99cbd, (void *)0x99e30, (void *)0x99c53, 0x36a);
        FUN_0007e2fa((unsigned long)0x99e71);
        FUN_0007e2ec((void *)0x99c53, 0x36a);
    } else if (mode == 0) {
        FUN_0007e2fa((unsigned long)0x99cbd, (void *)0x99e9d, (void *)0x99c53, 0x36e);
        FUN_0007e2fa((unsigned long)0x99ec7);
        FUN_0007e2ec((void *)0x99c53, 0x36e);
    } else if ((flags & 0x6400000) == 0x400000) {
        FUN_0007e2fa((unsigned long)0x99cbd, (void *)0x99ef2, (void *)0x99c53, 0x378);
        FUN_0007e2fa((unsigned long)0x99f3c);
        FUN_0007e2ec((void *)0x99c53, 0x378);
    }

    enabled = **(volatile uint32_t ***)(dev + 4);
    configure = *(pin_config_t *)(*(uintptr_t *)(dev + 8) + 0x18);
    output = **(volatile uint32_t ***)(dev + 16);
    bit = 1u << line;
    if ((*enabled & bit) == 0) {
        FUN_0007e2fa((unsigned long)0x99cbd, (void *)0x99de0, (void *)0x99c53, 0x382);
        FUN_0007e2fa((unsigned long)0x99e1e);
        FUN_0007e2ec((void *)0x99c53, 0x382);
    }
    if ((flags & 0x800000) && (*output & bit))
        flags ^= 0x6000000;
    configure(dev, line, flags & 0x1600000, flags & 0x6000000);
}
