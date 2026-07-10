#include "g1_app_symbols.h"
/* named: net_buf_simple_push */
/* Reconstructed net_buf_simple_push @ 0x5f518  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void net_buf_simple_push(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = (unsigned int)*param_1;
    char *r3 = (char*)param_1;
    unsigned int r1 = param_2;
    if ((unsigned int)(r0 - param_1[2]) < param_2) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "net_buf_simple_headroom(buf) >= len" /*=0xf5484*/, "WEST_TOPDIR/zephyr/subsys/net/buf_simple.c" /*=0xf543a*/, 0x12dUL);
        unsigned long long rv = assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf_simple.c" /*=0xf543a*/, 0x12dUL);
        r0 = (unsigned int)rv;
        r1 = (unsigned int)(rv >> 32);
        r3 = (char*)0x12dUL;
    }
    unsigned short r2 = *(volatile unsigned short*)(r3 + 4);
    *(volatile unsigned int*)r3 = r0 - r1;
    *(volatile short*)(r3 + 4) = (short)r1 + (short)r2;
}

