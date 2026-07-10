#include "g1_app_symbols.h"
/* named: net_buf_destroy_default */
/* Reconstructed net_buf_destroy_default @ 0x5f200  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void net_pkt_skip(void);

void net_buf_destroy_default(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "fifo" /*=0xf5402*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x1c7, param_4);
        uVar1 = 0x1c7;
    } else {
        if (param_2 != 0) {
            net_pkt_skip();
            return;
        }
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf" /*=0xf45be*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x1c8, param_4);
        uVar1 = 0x1c8;
    }
    assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, uVar1);
}

