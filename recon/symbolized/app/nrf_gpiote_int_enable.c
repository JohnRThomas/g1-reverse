#include "g1_app_symbols.h"
/* named: nrf_gpiote_int_enable */
/* Reconstructed nrf_gpiote_int_enable @ 0x65e10  (parity: 300/300 trials, PROVEN) */

extern unsigned int assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void nrf_gpiote_int_enable(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = param_1;
    if (*(volatile unsigned char*)((uintptr_t)&g_nrfx_gpiote_init_flag) /*=0x2000b328*/ != 1) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "m_cb.state == NRFX_DRV_STATE_INITIALIZED" /*=0xf6c09*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c" /*=0xf6bc5*/, 0x6c, param_4);
        r0 = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c" /*=0xf6bc5*/, 0x6c);
    }
    *(volatile int*)REG_5002a304 /*=0x5002a304*/ = 1 << (r0 & 0xff);
}

