#include "g1_app_symbols.h"
/* named: nrfx_dppi_channel_slot_reset */
/* Reconstructed nrfx_dppi_channel_slot_reset @ 0x67f1c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int a,unsigned int b);
extern void printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);

void nrfx_dppi_channel_slot_reset(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char idx = *(volatile unsigned char*)((char*)param_1+4);
    volatile unsigned char *tbl = (volatile unsigned char*)((uintptr_t)&m_dppi_channels) /*=0x2000b41c*/;
    int *basePtr;
    int idxVal;
    if (*(volatile char*)(tbl+idx*8) != 2) {
        unsigned long long r;
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"m_cb[p_instance->drv_inst_idx].state == NRFX_DRV_STATE_POWERED_ON" /*=0xf7a3f*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c" /*=0xf79c8*/,0xb8);
        r = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c" /*=0xf79c8*/,0xb8);
        basePtr = (int*)(unsigned int)(r & 0xffffffffUL);
        idxVal = (int)(unsigned int)(r >> 32);
    } else {
        basePtr = param_1;
        idxVal = param_2;
    }
    {
        int base = *(volatile int*)basePtr;
        *(volatile unsigned int*)(base + (idxVal+0x180)*4) = 0x6e524635UL;
    }
}

