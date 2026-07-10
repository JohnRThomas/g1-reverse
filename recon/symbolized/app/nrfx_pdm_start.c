#include "g1_app_symbols.h"
/* named: nrfx_pdm_start */
/* globals referenced:
//   0x2000b330  g_pdm_cb                     
*/
/* Reconstructed nrfx_pdm_start @ 0x66214  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void assert_post_action(unsigned int a0, unsigned int a1);

unsigned int nrfx_pdm_start(void)
{
    unsigned int iVar1 = ((uintptr_t)&g_pdm_cb) /*=0x2000b330*/;
    unsigned int uVar2;

    if (*(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/ + 0x10) != 0) {
        if (*(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/ + 0x11) == 0) {
            *(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/ + 0x11) = 2;
            *(volatile unsigned char*)(iVar1 + 0x14) = 1;
            *(volatile unsigned int*)(0xe000e100UL + 0x104) = 0x40;
            uVar2 = 0x0bad0000UL;
        } else {
            if (*(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/ + 0x11) != 1) {
                uVar2 = 0x0bad000bUL;
            } else {
                uVar2 = 0x0bad0000UL;
            }
        }
        return uVar2;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "m_cb.drv_state != NRFX_DRV_STATE_UNINITIALIZED" /*=0xf6d26*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/, 0xdd);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/, 0xdd);
    return 0;
}

