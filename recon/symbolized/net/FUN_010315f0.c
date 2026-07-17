#include "g1_net_symbols.h"
/* net-core rtc_nrf_isr @ 0x010315f0
 * Back-map: FUN_010315f0.  This is Zephyr's nRF RTC1 system-timer ISR with
 * CONFIG_SOC_NRF53_RTC_PRETICK enabled and two configured compare channels.
 * Raw callees: thunk_FUN_0102cfec @ 0x01039e4e,
 * FUN_0103a6ae @ 0x0103a6ae, FUN_010313a8 @ 0x010313a8.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

typedef void (*rtc_compare_handler_t)(int32_t channel,
                                      uint64_t expiration_time,
                                      void *user_context);

struct rtc_compare_data {
    rtc_compare_handler_t callback;
    void *user_context;
    volatile uint32_t target_time_low;
    volatile uint32_t target_time_high;
};

struct nrf_rtc_registers {
    uint32_t reserved_000[65];
    volatile uint32_t EVENTS_OVRFLW;       /* 0x104 */
    uint32_t reserved_108[14];
    volatile uint32_t EVENTS_COMPARE[4];  /* 0x140 */
    uint32_t reserved_150[109];
    volatile uint32_t INTENSET;            /* 0x304 */
    uint32_t reserved_308[16];
    volatile uint32_t EVTENCLR;            /* 0x348 */
};

/* Readable identities are retained at the call sites; this back-map records
 * the raw firmware symbols consumed by the parity linker. */
extern void rtc_pretick_rtc1_isr_hook(void); /* thunk_FUN_0102cfec */
extern void rtc_compare_event_clear(int32_t channel); /* FUN_0103a6ae */
extern uint64_t z_nrf_rtc_timer_read(void); /* FUN_010313a8 */

enum {
    RTC_OVERFLOW_INTERRUPT = 1u << 1,
    RTC_COMPARE_INTERRUPT_BASE = 1u << 16,
    RTC_COMPARE_CHANNEL_COUNT = 2,
};

void rtc_nrf_isr(const void *unused_argument)
{
    volatile struct nrf_rtc_registers *const rtc1 =
        (volatile struct nrf_rtc_registers *)0x41016000u;
    volatile uint32_t *const overflow_count =
        (volatile uint32_t *)((unsigned long)&g_rtc_overflow_cnt) /*=0x21004970*/;
    struct rtc_compare_data *const compare_data =
        (struct rtc_compare_data *)0x21002b60u;
    uint32_t *const force_isr_mask = (uint32_t *)0x21004964u;
    int32_t channel;

    (void)unused_argument;
    rtc_pretick_rtc1_isr_hook();

    if (((rtc1->INTENSET & RTC_OVERFLOW_INTERRUPT) != 0u) &&
        (rtc1->EVENTS_OVRFLW != 0u)) {
        rtc1->EVENTS_OVRFLW = 0u;
        (void)rtc1->EVENTS_OVRFLW;
        ++*overflow_count;
    }

    for (channel = 0; channel < RTC_COMPARE_CHANNEL_COUNT; ++channel) {
        const uint32_t interrupt_mask =
            RTC_COMPARE_INTERRUPT_BASE << (uint32_t)channel;

        if ((rtc1->INTENSET & interrupt_mask) != 0u) {
            const uint32_t channel_bit = 1u << (uint32_t)channel;
            const uint32_t forced = __atomic_fetch_and(
                force_isr_mask, ~channel_bit, __ATOMIC_ACQ_REL);

            if (((forced & channel_bit) != 0u) ||
                (rtc1->EVENTS_COMPARE[channel] != 0u)) {
                struct rtc_compare_data *const data = &compare_data[channel];
                uint64_t current_time;
                uint64_t expiration_time;
                rtc_compare_handler_t handler = 0;
                void *user_context = 0;
                uint32_t saved_primask;

                rtc_compare_event_clear(channel);
                current_time = z_nrf_rtc_timer_read();
                saved_primask = __get_PRIMASK();
                __disable_irq();

                expiration_time =
                    ((uint64_t)data->target_time_high << 32) |
                    data->target_time_low;
                if (current_time >= expiration_time) {
                    handler = data->callback;
                    user_context = data->user_context;
                    data->callback = 0;
                    /* Keep the two volatile words explicit: the shipped
                     * STRD is observed as two ordered peripheral-safe writes. */
                    data->target_time_low = UINT32_MAX;
                    data->target_time_high = UINT32_MAX;
                    rtc1->EVTENCLR = interrupt_mask;
                    rtc_compare_event_clear(channel);
                }

                __set_PRIMASK(saved_primask);
                if (handler != 0) {
                    handler(channel, expiration_time, user_context);
                }
            }
        }
    }
}
