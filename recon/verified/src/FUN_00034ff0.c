/* Reconstructed FUN_00034ff0 @ 0x34ff0 (strict CFG parity). */
#include <stdint.h>

extern void FUN_00019c70(uintptr_t format);
extern void FUN_0007dda4(uintptr_t format);
extern int FUN_00087036(const void *left, const void *right, uint32_t length);

uint32_t FUN_00034ff0(const void *name, const void *identifier)
{
    uint8_t *row;
    uint8_t *end;

    if (name == 0 || identifier == 0) {
        if (*(volatile uint32_t *)0x20007554U == 0) {
            FUN_0007dda4(0x000a8750U);
        } else {
            FUN_00019c70(0x000a8750U);
        }
        return 0;
    }

    row = (uint8_t *)0x2001a22cU;
    end = row + (uint32_t)*(volatile uint8_t *)0x2001a22dU * 0x38U;
    while (row != end) {
        if (FUN_00087036(row + 2, name, 0x28U) == 0 &&
            FUN_00087036(row + 0x2a, identifier, 0x10U) == 0) {
            return 1;
        }
        row += 0x38;
    }
    return 0;
}
