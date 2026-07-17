/* NCS 2.5.1 xfer_completeness_check @ 0x00085316 (FUN_00085316). */
#include <stdbool.h>
#include <stdint.h>

bool xfer_completeness_check(volatile uint8_t *twim,
                             const uint8_t *control_block)
{
    uint32_t expected;
    uint32_t actual;
    switch (control_block[0x20]) {
    case 0:
        expected = *(const uint32_t *)(control_block + 0x10);
        actual = *(volatile uint32_t *)(twim + 0x54c);
        break;
    case 1:
        expected = *(const uint32_t *)(control_block + 0x10);
        actual = *(volatile uint32_t *)(twim + 0x53c);
        break;
    case 2:
        if (*(const uint32_t *)(control_block + 0x10) !=
            *(volatile uint32_t *)(twim + 0x54c)) {
            goto incomplete;
        }
        expected = *(const uint32_t *)(control_block + 0x18);
        actual = *(volatile uint32_t *)(twim + 0x53c);
        break;
    case 3:
        if ((*(const uint32_t *)(control_block + 8) & (1u << 18)) != 0u) {
            if (*(const uint32_t *)(control_block + 0x10) !=
                *(volatile uint32_t *)(twim + 0x54c)) {
                goto incomplete;
            }
            return true;
        }
        expected = *(const uint32_t *)(control_block + 0x18);
        actual = *(volatile uint32_t *)(twim + 0x54c);
        break;
    default:
        return true;
    }
    if (expected == actual) {
        return true;
    }
incomplete:
    *(volatile uint32_t *)(twim + 0x500) = 0u;
    *(volatile uint32_t *)(twim + 0x500) = 6u;
    return false;
}
