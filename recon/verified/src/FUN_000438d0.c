/* Full reconstruction of FUN_000438d0 @ 0x438d0 (156-byte extent).
 * CFG_VERIFY_PREFIX_FIRST
 * The fixed 509,440-pixel sweep exceeds the generic instruction budget;
 * compare its first externally visible pixel write under reviewed state. */
#include <stdint.h>

struct display_state_438d0 {
    uint8_t reserved[0xeb4];
    void *destination;
    uint32_t destination_stride;
};

extern struct display_state_438d0 *FUN_000167a8(void);
extern void FUN_00047260(void *destination, uint32_t stride,
                         uint32_t x, uint32_t y, uint32_t width,
                         uint32_t height, uint32_t flags);
extern void FUN_000431c0(void);

int FUN_000438d0(uint32_t unused_a, uint32_t unused_b, uint32_t flags)
{
    uint8_t **rows = *(uint8_t ***)(uintptr_t)0x2000a034u;
    const uint8_t *masks = (const uint8_t *)(uintptr_t)0x000aae20u;

    (void)unused_a;
    (void)unused_b;
    for (uint32_t band = 0; band != 8; ++band) {
        for (uint32_t row = 0; row != 199; ++row) {
            uint8_t *pixels = rows[row];
            const uint8_t *mask = masks + (row % 26u) * 0xa00u
                                  + 0x8c0u - band * 0x140u;
            for (uint32_t column = 0; column != 0x140; ++column) {
                if (pixels[column] != 0)
                    pixels[column] &= mask[column];
            }
        }

        struct display_state_438d0 *state = FUN_000167a8();
        void *destination = state->destination;
        state = FUN_000167a8();
        FUN_00047260(destination, state->destination_stride, 0, 0,
                     0x280, 199, flags);
    }
    FUN_000431c0();
    return 0;
}
