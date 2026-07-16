/* Full reconstruction FUN_000361d8 @ 0x000361d8 (190-byte exact extent). */
#include <stdint.h>

extern void *FUN_000478d8(uintptr_t, uint16_t *);
extern uintptr_t FUN_0004792c(uint32_t, uint32_t, uint32_t);
extern void FUN_0007d4f8(void *, uintptr_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern uint8_t *FUN_000167a8(void);
extern int FUN_0004a300(uint32_t, void *);

int FUN_000361d8(void *destination)
{
    uint16_t count;
    uint8_t decoded[10] = {0};
    uint32_t groups[3];
    uint16_t *entries = FUN_000478d8(0x000a8d20u, &count);

    for (uint32_t i = 0; i < count; ++i) {
        uintptr_t value = FUN_0004792c(entries[i], 12, 36);
        FUN_0007d4f8((uint8_t *)destination + 36, value, 12, 36,
                     i * 12 + 6, 0);
    }

    uint8_t *state = FUN_000167a8();
    groups[0] = *(uint32_t *)(state + 0xef);
    groups[1] = *(uint32_t *)(state + 0xf3);
    groups[2] = *(uint32_t *)(state + 0xf7);
    for (uint32_t group = 0; group < 3; ++group) {
        int n = FUN_0004a300(groups[group], decoded);
        uint32_t row = (group + 1) * 30;
        for (int i = 0; i < n; ++i) {
            uintptr_t value = FUN_0004792c(decoded[i], 12, 36);
            FUN_0007d4f8((uint8_t *)destination + 36, value, 12, 36,
                         (uint32_t)i * 12 + 6, row);
        }
    }
    return 0;
}
