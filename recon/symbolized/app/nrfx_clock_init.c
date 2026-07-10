#include "g1_app_symbols.h"
/* named: nrfx_clock_init */
/* globals referenced:
//   0x2000b31c  g_clock_cb                   
*/
/* Reconstructed nrfx_clock_init @ 0x65190  (parity: 300/300 trials, PROVEN) */

extern unsigned int printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern unsigned int assert_post_action(unsigned int a,unsigned int b);

unsigned int nrfx_clock_init(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_clock_cb) /*=0x2000b31c*/;
    unsigned int uVar2;
    int inVal;
    if (param_1 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "event_handler" /*=0xf6abf*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_clock.c" /*=0xf6a4e*/, 0x115);
        inVal = (int)assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_clock.c" /*=0xf6a4e*/, 0x115);
    } else {
        inVal = param_1;
    }
    if (*(volatile unsigned char*)((char*)piVar1+4) == 0) {
        *piVar1 = inVal;
        uVar2 = 0x0bad0000UL;
        *(volatile unsigned char*)((char*)piVar1+4) = 1;
    } else {
        uVar2 = 0x0bad000cUL;
    }
    return uVar2;
}

