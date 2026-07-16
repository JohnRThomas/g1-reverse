/* Full reconstruction FUN_00035f28 @ 0x00035f28 (226-byte exact extent). */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t, ...);
extern void FUN_00019c70(uintptr_t, ...);
extern void FUN_000432ec(void);
extern void FUN_000432d0(void);
extern void FUN_00035afc(uint32_t, int);
extern void FUN_00074844(uint32_t, uint32_t);
extern uint8_t *FUN_000167a8(void);
extern void FUN_00047260(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

void FUN_00035f28(uint8_t **planes, uint32_t second, int enabled)
{
    if (!enabled || !planes) {
        uintptr_t format = enabled ? 0x000a8c42u : 0x000a8bcdu;
        uint32_t line = enabled ? 0x157u : 0x152u;
        if (*(volatile int32_t *)0x20007554u)
            FUN_00019c70(format, 0x000a8cd1u, line);
        else
            DEBUG_PRINT(format, 0x000a8cd1u, line);
        return;
    }

    FUN_000432ec();
    const uint32_t *masks = (const uint32_t *)0x000a8c57u;
    for (uint32_t pass = 0; pass < 8; ++pass) {
        FUN_00035afc(second, enabled);
        uint64_t packed = ((uint64_t)masks[1] << 32) | masks[0];
        for (uint32_t row = 0; row < 199; ++row) {
            uint8_t *pixels = planes[row];
            uint8_t selector = (packed >> (pass * 8)) & 0xffu;
            const uint8_t *mask = (const uint8_t *)(0x000aae20u +
                (uint32_t)selector * 0x140u + (row % 26u) * 0xa00u);
            for (uint32_t column = 0; column < 0x140; ++column)
                if (pixels[column]) pixels[column] &= mask[column];
        }
        FUN_00074844(0xa4, 0);
        uint8_t *state = FUN_000167a8();
        uint32_t first = *(uint32_t *)(state + 0xeb4);
        state = FUN_000167a8();
        FUN_00047260(first, *(uint32_t *)(state + 0xeb8), 0, 0, 0x280, 199);
    }
    FUN_000432d0();
}
