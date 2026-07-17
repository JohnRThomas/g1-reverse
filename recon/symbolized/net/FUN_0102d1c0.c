#include "g1_net_symbols.h"
/* net-core FUN_0102d1c0 @ 0x102d1c0 */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern uint32_t FUN_0103a6c6(void);

uint8_t FUN_0102d1c0(void)
{
    volatile uint8_t *const lock = (volatile uint8_t *)((unsigned long)&g_sdc_clock_calc_lock) /*=0x21004fab*/;
    volatile uint8_t *const enabled = (volatile uint8_t *)((unsigned long)&g_sdc_clock_calc_valid) /*=0x21004faa*/;
    volatile uint8_t *const cursor = (volatile uint8_t *)((unsigned long)&g_sdc_clock_history_idx) /*=0x21004fa8*/;
    volatile uint8_t *const wrapped = (volatile uint8_t *)((unsigned long)&g_sdc_clock_recalc_flag) /*=0x21004fa7*/;
    volatile uint32_t *const samples = (volatile uint32_t *)0x21004640u;
    volatile uint32_t *const timer_event = (volatile uint32_t *)REG_41005114 /*=0x41005114*/;
    volatile uint32_t *const radio_power = (volatile uint32_t *)REG_410121ac /*=0x410121ac*/;
    volatile uint32_t *const task_start = (volatile uint32_t *)REG_4100b004 /*=0x4100b004*/;
    uint8_t active;
    uint8_t next;
    uint32_t now;

    if (__STREXB(0, lock) != 0)
        goto disable;

    active = *enabled;
    if (active == 0)
        goto disable;

    next = (uint8_t)((*cursor + 1u) % 5u);
    now = FUN_0103a6c6();
    if (*wrapped != 0 && (uint32_t)(now - samples[next]) <= 7u)
        goto disable;

    if (*timer_event != 0) {
        *timer_event = 0;
        (void)*timer_event;
        *cursor = next;
        if (next == 0)
            *wrapped = 1;
    }
    next = *cursor;
    samples[next] = FUN_0103a6c6();
    return active;

disable:
    *radio_power &= 0x7fffffffu;
    *task_start = 1;
    return 0;
}
