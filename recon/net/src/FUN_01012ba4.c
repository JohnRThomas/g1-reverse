/* net-core FUN_01012ba4 @ 0x1012ba4  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(uint32_t a, uint32_t b, uint32_t c,
                         uint32_t d, uint32_t e) __attribute__((noreturn));

uint32_t FUN_01012ba4(int32_t param_1, int32_t param_2, uint32_t param_3, uint32_t param_4)
{
    uint32_t uVar1 = (uint32_t)(param_1 - 1) & 0xff;

    if ((uVar1 > 1) && (param_2 != 0x1d)) {
        FUN_01008d00(0x2f, 0xee, param_3, uVar1, param_4);
    }

    const uint32_t base = 0x0103c1d4;

    switch (param_2) {
    case 0x10:
        return (uint32_t) *(volatile uint16_t *)(base + uVar1 * 2 + 0x18);
    case 0x12:
    case 0x13:
        return (uint32_t) *(volatile uint16_t *)(base + uVar1 * 2 + 0x20);
    case 0x15:
        return (uint32_t) *(volatile uint16_t *)(base + uVar1 * 2 + 0x1c);
    case 0x1d:
        return (uint32_t)(param_1 * 0x35a);
    default:
        FUN_01008d00(0x2f, 0x102, param_3, uVar1, param_4);
    }
}
