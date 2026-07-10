#include "g1_app_symbols.h"
/* named: gpio_configure_pin_output */
/* Reconstructed gpio_configure_pin_output @ 0x6666c  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned,unsigned,unsigned,unsigned,unsigned);
extern long long assert_post_action(unsigned,unsigned);
void gpio_configure_pin_output(unsigned param_1, int param_2, unsigned param_3, unsigned param_4){
    unsigned r0v = param_1;
    unsigned r1v = (unsigned)param_2;
    unsigned uVar2; int iVar1;
    if ((param_1 >> 5) == 0) goto L_68e;
    if ((param_1 >> 5) == 1) goto L_6b4;
L_676:
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"nrf_gpio_pin_present_check(*p_pin)" /*=0xf0a04*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_gpio.h" /*=0xf09d1*/,0x32f,param_4);
    { long long r = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_gpio.h" /*=0xf09d1*/,0x32f);
      r0v = (unsigned)r; r1v = (unsigned)((unsigned long long)r >> 32); }
L_68e:
    { unsigned s = r0v & 0xff; uVar2 = (s >= 32) ? 0u : (0xffffffffu >> s); }
    iVar1 = 0x50842500;
    if ((int)(uVar2 << 0x1f) >= 0) goto L_676;
    goto L_join;
L_6b4:
    r0v = param_1 & 0x1f;
    uVar2 = ((uintptr_t)&tbl_ffc8) /*=0xffff*/ >> r0v;
    iVar1 = 0x50842800;
    if ((int)(uVar2 << 0x1f) >= 0) goto L_676;
L_join:
    {
        volatile unsigned* addr = (volatile unsigned*)(iVar1 + (r0v << 2) + 0x200);
        *addr = (*addr & 0xfffcf0f0) | (r1v << 8) | 2;
    }
}

