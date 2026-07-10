#include "g1_app_symbols.h"
/* named: gatt_sub_free */
/* Reconstructed gatt_sub_free @ 0x59e78  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_000828da(void *a, unsigned int b, unsigned int c, unsigned int d);

void gatt_sub_free(char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (*(volatile int*)(param_1 + 8) != 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "gatt_sub_is_empty(sub)" /*=0xf4707*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0xd5c);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0xd5c);
    }
    FUN_000828da(param_1 + 1, ((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/, param_3, param_4);
}

