#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102d0c4 @ 0x0102d0c4
 * public-name: FUN_0102d0c4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_rtc_timer_sync_valid               @ 0x21004fa9
 *   g_sdc_clock_calc_valid                   @ 0x21004faa
 *   g_sdc_clock_calc_lock                    @ 0x21004fab
 *   REG_4100b000                             @ 0x4100b000
 */
/* net-core FUN_0102d0c4 @ 0x102d0c4
 *
 * Exact stock owner: Zephyr 3.4.99-ncs1-1
 *   soc/arm/nordic_nrf/nrf53/soc.c:z_arm_on_enter_cpu_idle_prepare
 *
 * Keep the raw linker identity while exposing the recovered stock name in
 * the C body.  The fixed addresses below are the linked NRF53 CPUNET objects
 * and MMIO instances from the shipped image.
 */
#include <stdbool.h>
#include <stdint.h>
#include <cmsis_gcc.h>

#define z_arm_on_enter_cpu_idle_prepare FUN_0102d0c4
#define rtc_pretick_finish_previous FUN_0102cfec
#define rtc_ticks_to_next_event_get FUN_01039dec

extern void rtc_pretick_finish_previous(void);
extern bool rtc_ticks_to_next_event_get(volatile void *rtc,
                                        uint32_t selected_cc_mask,
                                        uint32_t counter,
                                        uint32_t *ticks_to_next_event);

#define CPU_IDLE_PREPARE_MONITOR_DUMMY ((volatile uint8_t *)((unsigned long)&g_sdc_clock_calc_lock) /*=0x21004fab*/)
#define RTC_PRETICK_CC_SET_ON_TIME      ((volatile bool *)((unsigned long)&g_net_rtc_timer_sync_valid) /*=0x21004fa9*/)
#define CPU_IDLE_PREPARE_ALLOWS_SLEEP  ((volatile bool *)((unsigned long)&g_sdc_clock_calc_valid) /*=0x21004faa*/)

#define NRF_WDT_BASE   REG_4100b000 /*=0x4100b000*/
#define NRF_RTC0_BASE  0x41011000u
#define NRF_IPC_BASE   0x41012000u
#define NRF_RTC1_BASE  0x41016000u

#define RTC_COUNTER_OFFSET       0x504u
#define RTC_PRETICK_CC_OFFSET    0x54cu
#define RTC_PRETICK_EVENT_OFFSET 0x14cu
#define IPC_PUBLISH_OFFSET       0x1acu

#define RTC_COUNTER_MAX       0x00ffffffu
#define RTC_COUNTER_HALF_SPAN 0x007fffffu

static inline uint32_t mmio_read32(uintptr_t address)
{
    return *(volatile uint32_t *)address;
}

static inline void mmio_write32(uintptr_t address, uint32_t value)
{
    *(volatile uint32_t *)address = value;
}

static inline uint32_t rtc_counter_sub(uint32_t a, uint32_t b)
{
    return (a - b) & RTC_COUNTER_MAX;
}

void z_arm_on_enter_cpu_idle_prepare(void)
{
    bool ok_to_sleep = true;
    uint32_t rtc_counter = 0;
    uint32_t rtc_ticks_to_next_event = 0;
    uint32_t rtc0_counter = 0;
    uint32_t rtc0_ticks_to_next_event = 0;

    /* Begin the exception-preemption monitor paired with the STREXB in
     * z_arm_on_enter_cpu_idle().  An ordinary volatile read is not equivalent.
     */
    (void)__LDREXB(CPU_IDLE_PREPARE_MONITOR_DUMMY);

    do {
        rtc_counter = mmio_read32(NRF_RTC1_BASE + RTC_COUNTER_OFFSET);
        __DMB();
        rtc0_counter = mmio_read32(NRF_RTC0_BASE + RTC_COUNTER_OFFSET);
        __DMB();
    } while (rtc_counter !=
             mmio_read32(NRF_RTC1_BASE + RTC_COUNTER_OFFSET));

    bool rtc_scheduled = rtc_ticks_to_next_event_get(
        (volatile void *)NRF_RTC1_BASE, 3u, rtc_counter,
        &rtc_ticks_to_next_event);

    if (rtc_ticks_to_next_event_get(
            (volatile void *)NRF_RTC0_BASE, 0x0fu, rtc0_counter,
            &rtc0_ticks_to_next_event)) {
        if (!rtc_scheduled ||
            rtc0_ticks_to_next_event < rtc_ticks_to_next_event) {
            rtc_ticks_to_next_event = rtc0_ticks_to_next_event;
            rtc_scheduled = true;
        }
    }

    if (rtc_scheduled) {
        uint32_t rtc_pretick_cc_val =
            (rtc_counter + rtc_ticks_to_next_event - 1u) & RTC_COUNTER_MAX;

        if (rtc_pretick_cc_val !=
            mmio_read32(NRF_RTC1_BASE + RTC_PRETICK_CC_OFFSET)) {
            rtc_pretick_finish_previous();
            mmio_write32(NRF_RTC1_BASE + RTC_PRETICK_CC_OFFSET,
                         rtc_pretick_cc_val);

            if (rtc_ticks_to_next_event >= RTC_COUNTER_HALF_SPAN) {
                *RTC_PRETICK_CC_SET_ON_TIME = true;
            } else {
                __DMB();
                rtc_counter =
                    mmio_read32(NRF_RTC1_BASE + RTC_COUNTER_OFFSET);
                uint32_t pretick_cc_to_counter =
                    rtc_counter_sub(rtc_pretick_cc_val, rtc_counter);

                if (pretick_cc_to_counter < 3u ||
                    pretick_cc_to_counter >= RTC_COUNTER_HALF_SPAN) {
                    *RTC_PRETICK_CC_SET_ON_TIME = false;
                } else {
                    *RTC_PRETICK_CC_SET_ON_TIME = true;
                }
            }
        }

        ok_to_sleep = *RTC_PRETICK_CC_SET_ON_TIME;
    }

    if (ok_to_sleep) {
        uintptr_t publish = NRF_IPC_BASE + IPC_PUBLISH_OFFSET;
        mmio_write32(publish, mmio_read32(publish) | 0x80000000u);

        if (mmio_read32(NRF_RTC1_BASE + RTC_PRETICK_EVENT_OFFSET) == 0u) {
            mmio_write32(NRF_WDT_BASE + 4u, 1u);
            if (mmio_read32(NRF_RTC1_BASE + RTC_PRETICK_EVENT_OFFSET) != 0u) {
                mmio_write32(NRF_WDT_BASE, 1u);
            }
        }
    }

    *CPU_IDLE_PREPARE_ALLOWS_SLEEP = ok_to_sleep;
}
