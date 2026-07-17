/* Reconstructed spim_pin_uninit @ 0x67138  (CFG-directed candidate) */
#include <stdint.h>
extern uintptr_t FUN_00066d1c(uint32_t *pin);
void spim_pin_uninit(uint32_t pin, uint32_t unused, uint32_t context)
{
    (void)unused;
    (void)context;
    if (pin != UINT32_MAX) {
        uint32_t normalized = pin;
        uintptr_t gpio = FUN_00066d1c(&normalized);
        volatile uint32_t *config = (volatile uint32_t *)(gpio + 0x200u + normalized * 4u);
        *config = (*config & 0xfffcf0f0u) | 2u;
    }
}
