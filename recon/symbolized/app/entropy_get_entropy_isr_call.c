#include "g1_app_symbols.h"
/* named: entropy_get_entropy_isr_call */
/* globals referenced:
//   0x00087b90  entropy_dev                  
*/
/* Reconstructed entropy_get_entropy_isr_call @ 0x52bf8  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int assert_post_action(unsigned int a, unsigned int b);

void entropy_get_entropy_isr_call(unsigned int param_1, unsigned int param_2)
{
    volatile unsigned int *pp = (volatile unsigned int*)(((uintptr_t)&entropy_dev) /*=0x87b90*/ + 8);
    unsigned int A = *pp;
    unsigned int r4 = *(volatile unsigned int*)A;
    unsigned int arg1, arg2;
    if (r4 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "api->get_entropy != ((void *)0)" /*=0xf2a79*/, "WEST_TOPDIR/zephyr/include/zephyr/drivers/entropy.h" /*=0xf2a45*/, 0x4d);
        printk("\tCallback pointer should not be NULL\n" /*=0xf2a99*/, 0, 0, 0);
        assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/drivers/entropy.h" /*=0xf2a45*/, 0x4d);
        arg1 = 0x4d;
        arg2 = "WEST_TOPDIR/zephyr/include/zephyr/drivers/entropy.h" /*=0xf2a45*/;
    } else {
        arg1 = param_1;
        arg2 = param_2;
    }
    {
        void (*fp)(unsigned int, unsigned int, unsigned int) = (void (*)(unsigned int,unsigned int,unsigned int))r4;
        fp(((uintptr_t)&entropy_dev) /*=0x87b90*/, arg1, arg2);
    }
}

