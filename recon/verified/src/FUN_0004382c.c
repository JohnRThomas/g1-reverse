/* Full reconstruction of FUN_0004382c @ 0x4382c (164 bytes). */
#include <stdint.h>

extern void *FUN_000167a8(void);
extern void FUN_00047260(uint32_t left, uint32_t right, uint32_t x,
                        uint32_t y, uint32_t width, uint32_t height);
extern void FUN_00086384(uint32_t delay);
extern void FUN_000431c0(void);

int FUN_0004382c(void)
{
    int32_t mask_row = 0;
    do {
        uint32_t **rows = *(uint32_t ***)0x2000a034u;
        for (uint32_t row = 0; row != 199; ++row) {
            uint8_t *destination = (uint8_t *)rows[row];
            const uint8_t *mask = (const uint8_t *)(0x000aae20u + 0x8c0u +
                (row % 26u) * 0xa00u + mask_row);
            for (uint32_t column = 0; column != 0x140; ++column) {
                if (destination[column] != 0)
                    destination[column] &= mask[column];
            }
        }

        const uint8_t *display = (const uint8_t *)FUN_000167a8();
        uint32_t left = *(const uint32_t *)(display + 0xeb4);
        display = (const uint8_t *)FUN_000167a8();
        uint32_t right = *(const uint32_t *)(display + 0xeb8);
        FUN_00047260(left, right, 0, 0, 0x280, 199);
        mask_row -= 0x140;
        FUN_00086384(5000);
    } while (mask_row != -0xa00);

    FUN_000431c0();
    return 0;
}
