#include "g1_app_symbols.h"
/* named: nrfx_pdm_stop */
/* Reconstructed nrfx_pdm_stop @ 0x66300  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern void assert_post_action(int a, int b);

unsigned int nrfx_pdm_stop(void)
{
    unsigned char bVar1;
    unsigned int uVar3;

    if (*(volatile unsigned char *)((uintptr_t)&nrfx_pdm_drv_state) /*=0x2000b340*/ == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "m_cb.drv_state != NRFX_DRV_STATE_UNINITIALIZED" /*=0xf6d26*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/, 0x132, 0);
        assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/, 0x132);
    }
    bVar1 = *(volatile unsigned char *)((uintptr_t)&nrfx_pdm_state) /*=0x2000b341*/;
    if (bVar1 == 1) {
        *(volatile unsigned char *)((uintptr_t)&nrfx_pdm_drv_state) /*=0x2000b340*/ = 1;
        *(volatile unsigned char *)((uintptr_t)&nrfx_pdm_state) /*=0x2000b341*/ = 3;
        *(volatile unsigned int *)REG_50026004 /*=0x50026004*/ = (unsigned int)bVar1;
        uVar3 = 0x0bad0000;
    } else if (bVar1 == 0 || bVar1 == 2) {
        *(volatile unsigned int *)REG_50026500 /*=0x50026500*/ = 0;
        *(volatile unsigned char *)((uintptr_t)&nrfx_pdm_state) /*=0x2000b341*/ = 0;
        uVar3 = 0x0bad0000;
    } else {
        uVar3 = 0x0bad000b;
    }
    return uVar3;
}

