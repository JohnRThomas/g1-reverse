#include "g1_app_symbols.h"
/* named: nrfx_pdm_init */
/* globals referenced:
//   0x2000b330  g_pdm_cb                     
*/
/* Reconstructed nrfx_pdm_init @ 0x6615c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned,unsigned,unsigned,unsigned);
extern long long assert_post_action(unsigned,unsigned);
extern void pdm_configure_pins(void);
unsigned nrfx_pdm_init(int param_1, int param_2){
    unsigned r0v = (unsigned)param_1;
    unsigned r1v = (unsigned)param_2;
    if (r0v != 0) goto L_174;
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"p_config" /*=0xf6c00*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/,0x78);
    { long long r=assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/,0x78); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32);}
L_174:
    if (r1v != 0) goto L_186;
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"event_handler" /*=0xf6abf*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/,0x79);
    { long long r=assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c" /*=0xf6ceb*/,0x79); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32);}
    goto L_174;
L_186:
    {
        volatile unsigned char* p = (volatile unsigned char*)((uintptr_t)&g_pdm_cb) /*=0x2000b330*/;
        if (*(volatile unsigned char*)(p + 0x10) != 0) return 0xbad0005;
        *(volatile int*)(p + 4) = 0;
        *(volatile int*)(p + 8) = 0;
        *(volatile unsigned short*)(p + 0x12) = 0;
        *(volatile unsigned char*)(p + 0x11) = 0;
        unsigned char uVar1 = *(unsigned char*)(r0v + 0x15);
        *(volatile int*)p = (int)r1v;
        *(volatile unsigned char*)(p + 0x15) = uVar1;
        if (*(unsigned char*)(r0v + 0x10) > 0x50) return 0xbad0004;
        if (*(unsigned char*)(r0v + 0x11) > 0x50) return 0xbad0004;
        pdm_configure_pins();
        *(volatile unsigned char*)(p + 0x10) = 1;
        return 0xbad0000;
    }
}

