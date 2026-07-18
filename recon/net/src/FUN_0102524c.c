/* net-core FUN_0102524c @ 0x0102524c -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

static inline void sync_barriers(void)
{
    __asm__ volatile("dsb sy\n\tisb sy" ::: "memory");
}

void FUN_0102524c(uint32_t channel)
{
    volatile uint32_t *const radio = (volatile uint32_t *)0x4100c000u;
    volatile uint8_t *const state = (volatile uint8_t *)0x21001bf8u;

    if (channel < 4) {
        uint32_t mask = 1u << (channel + 16u);
        radio[0x308 / 4] = mask;
        radio[(0x540 / 4) + channel] = 0;
        radio[(0x140 / 4) + channel] = 0;
        return;
    }

    uint32_t index = (uint8_t)(channel - 4u);
    if (index > 1)
        controller_fault(0x6c, 0x430);

    if (state[0] != 0 && state[1] == channel) {
        volatile uint32_t *const timer0 = (volatile uint32_t *)0x4100f000u;
        timer0[0x508 / 4] = 6;
        if (state[0] == 1) {
            volatile uint32_t *const nvic = (volatile uint32_t *)0xe000e100u;
            nvic[0x80 / 4] = 0x1000;
            sync_barriers();
            nvic[0x180 / 4] = 0x1000;
            radio[1] = 1;
            state[0x14] = 0;
            radio[0x308 / 4] = 0xffffffffu;
            for (uint32_t i = 0; i < 4; ++i) {
                radio[(0x540 / 4) + i] = 0;
                radio[(0x140 / 4) + i] = 0;
            }
        }
        state[0] = 0;
        *(volatile uint32_t *)(state + 8) = 0xffffffffu;
        *(volatile uint32_t *)(state + 12) = 0xffffffffu;
    }

    volatile uint32_t *const timer1 = (volatile uint32_t *)0x41011000u;
    uint32_t mask = 0x10000u << index;
    timer1[0x308 / 4] = mask;
    timer1[0x348 / 4] = mask;
    uint32_t delta = timer1[(0x540 / 4) + index] - timer1[0x504 / 4];
    if ((delta & 0x00fffffeu) != 0)
        timer1[(0x140 / 4) + index] = 0;
}
