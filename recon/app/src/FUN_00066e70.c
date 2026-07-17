/* Reconstructed pin_init @ 0x00066e70 (FUN_00066e70; CFG-verified). */
/* Pinned nrfx_spim.c static helper; raw public identity retained for backmapping. */
#include <stdint.h>
extern uintptr_t FUN_00066d1c(uint32_t *descriptor);
extern void FUN_000852e6(uint32_t pin);
extern void FUN_000852fe(uint32_t pin);
void FUN_00066e70(uint32_t pin, uint32_t output, uint32_t pull,
                  uint32_t drive, uint32_t initial_state)
{
    if (pin == UINT32_MAX) return;
    if (output == 1u) {
        if (initial_state != 0u) FUN_000852e6(pin);
        else FUN_000852fe(pin);
    }
    uint32_t descriptor = pin;
    uintptr_t port = FUN_00066d1c(&descriptor);
    volatile uint32_t *cnf = (volatile uint32_t *)(port + descriptor * 4u + 0x200u);
    *cnf = (*cnf & 0xfffcf0f0u) | (drive << 8) | (pull << 2) |
           output | (output << 1);
}
