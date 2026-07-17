/* Reconstructed FUN_0003483c @ 0x3483c (strict CFG parity). */
#include <stdint.h>

extern uint8_t FUN_0000ef12(const char *text);
extern uintptr_t FUN_000167a8(void);
extern int FUN_00087036(const void *left, const void *right, uint32_t length);

static uint32_t bounded_length(const char *text)
{
    uint32_t length = FUN_0000ef12(text);
    return length < 31U ? length : 31U;
}

int FUN_0003483c(int slot, uint32_t unused_2, uint32_t unused_3,
                 uint32_t unused_4)
{
    uint8_t *record = (uint8_t *)(0x20007dbcU + (uint32_t)slot * 0x1b4U);
    const char *row;

    (void)unused_2;
    (void)unused_3;
    (void)unused_4;

    if (FUN_00087036((const void *)0x000a819eU, record, 0x18U) == 0 ||
        FUN_00087036((const void *)0x0009adaaU, record, 0x1cU) == 0) {
        return 1;
    }
    if (FUN_00087036((const void *)0x000a81b7U, record, 0x18U) == 0 ||
        FUN_00087036((const void *)0x000a81d0U, record, 0x15U) == 0) {
        return 2;
    }
    if (FUN_00087036((const void *)0x000a81e6U, record, 0x13U) == 0 ||
        FUN_00087036((const void *)0x000a81faU, record, 0x14U) == 0) {
        return 0;
    }

    row = *(volatile uint8_t *)(FUN_000167a8() + 0x1068U) != 0
        ? (const char *)0x20003292U : (const char *)0x20003152U;
    while (*(volatile const uint8_t *)row != 0) {
        if (FUN_00087036(row, record, bounded_length(row)) == 0) {
            return 3;
        }
        row += 0x20;
    }

    row = *(volatile uint8_t *)(FUN_000167a8() + 0x1068U) != 0
        ? (const char *)0x200030d2U : (const char *)0x20003032U;
    while (*(volatile const uint8_t *)row != 0) {
        if (FUN_00087036(row, record, bounded_length(row)) == 0) {
            return 4;
        }
        row += 0x20;
    }
    return 5;
}
