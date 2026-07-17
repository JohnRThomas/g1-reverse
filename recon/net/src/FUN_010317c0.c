/* Zephyr sys_clock_elapsed @ 0x010317c0, exact executable extent 0x0e.
 * Raw/address backmaps:
 *   FUN_010317c0@0x010317c0
 *   z_nrf_rtc_timer_read = FUN_010313a8@0x010313a8
 *   last_count@0x21002b80
 * The function returns at 0x010317cc; its literal starts at 0x010317d0.
 */
#include <stdint.h>
#define sys_clock_elapsed FUN_010317c0

extern uint32_t FUN_010313a8(void);
#define z_nrf_rtc_timer_read FUN_010313a8

uint32_t sys_clock_elapsed(void)
{
    volatile const uint32_t *last_count =
        (volatile const uint32_t *)0x21002b80u;

    return z_nrf_rtc_timer_read() - *last_count;
}
