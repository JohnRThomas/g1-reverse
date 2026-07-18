/* net-core FUN_01024c6c @ 0x01024c6c -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

static inline void sync_barriers(void)
{
    __asm__ volatile("dsb sy\n\tisb sy" ::: "memory");
}

uint64_t FUN_01024c6c(uint32_t timestamp, int32_t context)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x21001bf8u;
    volatile uint32_t *const timer0 = (volatile uint32_t *)0x4100f000u;
    volatile uint32_t *timer;
    uint8_t prior = state[0];

    if (prior == 1) {
        if (*(volatile int32_t *)(state + 12) == context &&
            *(volatile uint32_t *)(state + 8) == timestamp)
            return ((uint64_t)(uint32_t)context << 32) | timestamp;
        timer0[0x508 / 4] = 6;
    } else {
        timer0[0x508 / 4] = 6;
        if (prior == 0) {
            timer = (volatile uint32_t *)0x41011000u;
            timer[0x348 / 4] = 0x30000;
            timer[0x308 / 4] = 0x30000;
            timer[0x140 / 4] = 0;
            timer[0x308 / 4] = 0x10000;
            timer[0x348 / 4] = 0x10000;
            timer[0x140 / 4] = 0;
            uint32_t target = timestamp & 0x00ffffffu;
            uint32_t delta = target - timer[0x504 / 4];
            if ((delta & 0x00fffffeu) == 0 ||
                (delta & 0x00ffffffu) > 0x00800000u)
                controller_fault(0x6c, 0x30e);
            timer[0x540 / 4] = target;
            timer[0x344 / 4] = 0x10000;
            goto configure;
        }
    }

    timer = (volatile uint32_t *)0x41011000u;
    timer[0x348 / 4] = 0x20000;
    timer[0x308 / 4] = 0x20000;
    timer[0x308 / 4] = 0x10000;
    timer[0x348 / 4] = 0x10000;
    timer[0x140 / 4] = 0;
    uint32_t target = timestamp & 0x00ffffffu;
    uint32_t delta = target - timer[0x504 / 4];
    if ((delta & 0x00fffffeu) == 0 ||
        (delta & 0x00ffffffu) > 0x00800000u)
        controller_fault(0x6c, 0x30e);
    timer[0x540 / 4] = target;
    timer[0x344 / 4] = 0x10000;
    if (prior != 0)
        while (((*(volatile uint32_t *)(state + 8) - timer[0x504 / 4]) &
                0x00fffffeu) == 0) { }

configure:;
    volatile uint32_t *const nvic = (volatile uint32_t *)0xe000e100u;
    *(volatile uint32_t *)(state + 0x1c) = 1;
    state[2] = 0;
    nvic[0x80 / 4] = 0x1000;
    sync_barriers();
    nvic[0x180 / 4] = 0x1000;
    state[0x14] = 0;
    radio_reset: {
        volatile uint32_t *const radio = (volatile uint32_t *)0x4100c000u;
        radio[1] = 1;
        radio[0x308 / 4] = 0xffffffffu;
        for (uint32_t i = 0; i < 4; ++i) {
            radio[(0x540 / 4) + i] = 0;
            radio[(0x140 / 4) + i] = 0;
        }
        radio[0x504 / 4] &= ~3u;
        radio[0x508 / 4] = (radio[0x508 / 4] & ~3u) | 2u;
        radio[0x510 / 4] = 4;
        *(volatile uint32_t *)(state + 8) = timestamp;
        radio[3] = 1;
        *(volatile int32_t *)(state + 12) = context;
        radio[0x200 / 4] = *(volatile uint32_t *)(state + 0x1c);
        nvic[0x180 / 4] = 0x1000;
        nvic[0] = 0x1000;
        timer[0x1c0 / 4] = 0x80000002u;
        radio[0x80 / 4] = 0x80000002u;
        ((volatile uint32_t *)0x4100f000u)[0x504 / 4] = 4;
        *(volatile uint16_t *)state = 0x0401u;
    }
    (void)&&radio_reset;
    return (UINT64_C(0x401) << 32) | UINT64_C(0x4100f000);
}
