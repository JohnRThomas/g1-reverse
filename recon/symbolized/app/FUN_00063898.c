#include "g1_app_symbols.h"
/* named: FUN_00063898 */
/* Reconstructed FUN_00063898 @ 0x63898  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void FUN_00063898(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 1) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "chan > 0 && chan < (1 + 1)" /*=0xf66a6*/, "WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0x257UL);
        assert_post_action("WEST_TOPDIR/zephyr/drivers/timer/nrf_rtc_timer.c" /*=0xf6659*/, 0x257UL);
    }
    *(volatile unsigned int*)((uintptr_t)&nrf_rtc_timer_free_channels) /*=0x2000b2d4*/ |= 2;
}

