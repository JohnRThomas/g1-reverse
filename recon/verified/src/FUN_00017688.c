/* app-core FUN_00017688 @ 0x00017688 */
#include <stdint.h>

extern void FUN_0007e2fa(const void *, ...);
extern void FUN_0007e2ec(const void *, unsigned);

void FUN_00017688(const uint8_t *pin, uint32_t flags)
{
    uintptr_t dev = *(const uint32_t *)pin;
    uint32_t combined = *(const uint16_t *)(pin + 6) | flags;
    unsigned line = pin[4];
    uint32_t bit;
    volatile uint32_t *enabled;
    volatile uint32_t *output;
    void (**api)(void);

    if ((combined & 0x30) == 0x30) {
        FUN_0007e2fa((void *)0x99cbd, (void *)0x99c84, (void *)0x99c53, 0x3ca);
        FUN_0007e2fa((void *)0x99cda);
        FUN_0007e2ec((void *)0x99c53, 0x3ca);
    } else if ((combined & 0x30002) == 0x10002) {
        FUN_0007e2fa((void *)0x99cbd, (void *)0x99d17, (void *)0x99c53, 0x3ce);
        FUN_0007e2fa((void *)0x99d5e);
        FUN_0007e2ec((void *)0x99c53, 0x3ce);
    } else if ((combined & 6) == 4) {
        FUN_0007e2fa((void *)0x99cbd, (void *)0x99dad, (void *)0x99c53, 0x3d1);
        FUN_0007e2ec((void *)0x99c53, 0x3d1);
    }

    enabled = **(volatile uint32_t ***)(dev + 4);
    api = *(void (***)(void))(dev + 8);
    output = **(volatile uint32_t ***)(dev + 16);
    bit = 1u << line;
    if ((*enabled & bit) == 0) {
        FUN_0007e2fa((void *)0x99cbd, (void *)0x99de0, (void *)0x99c53, 0x3e4);
        FUN_0007e2fa((void *)0x99e1e);
        FUN_0007e2ec((void *)0x99c53, 0x3e4);
    }
    if (combined & 1)
        *output |= bit;
    else
        *output &= ~bit;
    (*api)();
}
