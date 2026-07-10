#include "g1_app_symbols.h"
/* named: FUN_000681cc */
/* Reconstructed FUN_000681cc @ 0x681cc  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(int,int);
extern void printk(int,int,int,int);
typedef void (*fn2_t)(int,int);
void FUN_000681cc(int param_1)
{
    int iVar1;
    if ((param_1 != 0) && ((iVar1 = *(volatile int*)(param_1 + 4)) != 0)) {
        fn2_t f = *(volatile fn2_t*)(iVar1 + 0xc);
        if (f != 0) {
            f(iVar1, param_1);
            return;
        }
        return;
    }
    printk("device && device->bus" /*=0xf7ad6*/, "ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "WEST_TOPDIR/modules/hal/libmetal/libmetal/lib/device.c" /*=0xf7a9f*/, 0x51);
    assert_post_action("WEST_TOPDIR/modules/hal/libmetal/libmetal/lib/device.c" /*=0xf7a9f*/, 0x51);
}

