#include "g1_net_symbols.h"
/* net-core FUN_010250d0 @ 0x10250d0 */
#include <stdbool.h>
#include <stdint.h>

extern void FUN_010256dc(uint32_t subsystem, uint32_t reason);

static __attribute__((noreturn)) void panic_forever(uint32_t first_reason)
{
    FUN_010256dc(0x6c, first_reason);
    for (;;)
        FUN_010256dc(0x6c, 0x3a3);
}

bool FUN_010250d0(uint32_t channel, uint32_t unused, uint32_t timestamp)
{
    volatile uint8_t *const state = (volatile uint8_t *)UINT32_C(0x21001bf8);
    timestamp &= UINT32_C(0x00ffffff);

    if (channel < 4) {
        volatile uint32_t *const radio =
            (volatile uint32_t *)UINT32_C(0x4100c000);

        if (*(volatile int32_t *)(state + 8) == -1 &&
            *(volatile int32_t *)(state + 12) == -1 && state[0x14] == 0)
            FUN_010256dc(0x6c, 0x384);

        if (state[0] == 2 && state[1] > 3) {
            volatile uint32_t *ready =
                (volatile uint32_t *)(UINT32_C(0x41011140) +
                                      (uint8_t)(state[1] - 4) * 4);
            while (*ready == 0) { }
        }

        uint32_t mask = UINT32_C(1) << (channel + 16);
        radio[0x308 / 4] = mask;
        radio[(0x40 / 4) + channel] = 1;

        volatile uint32_t *capture =
            (volatile uint32_t *)((uintptr_t)radio + 0x540 + channel * 4);
        if (((timestamp - *capture) & UINT32_C(0x00ffffff)) > 2) {
            *capture = timestamp;
            radio[0x304 / 4] = mask;
            return true;
        }

        *capture = 0;
        return false;
    }

    uint32_t index = (uint8_t)(channel - 4);
    if (index > 1)
        panic_forever(0x3a7);
    if (state[0] != 0 && state[1] == channel)
        panic_forever(0x3a3);

    volatile uint32_t *const timer =
        (volatile uint32_t *)UINT32_C(0x41011000);
    uint32_t mask = UINT32_C(0x10000) << index;
    timer[0x308 / 4] = mask;
    timer[0x348 / 4] = mask;
    timer[(0x140 / 4) + index] = 0;

    uint32_t delta = timestamp - timer[0x504 / 4];
    bool valid = (delta & UINT32_C(0x00fffffe)) != 0 &&
                 (delta & UINT32_C(0x00ffffff)) <= UINT32_C(0x00800000);
    if (valid) {
        timer[0x540 / 4 + index] = timestamp;
        timer[0x304 / 4] = mask;
        timer[0x344 / 4] = mask;
    }
    return valid;
}
