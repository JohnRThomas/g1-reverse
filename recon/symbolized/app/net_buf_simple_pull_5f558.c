#include "g1_app_symbols.h"
/* named: net_buf_simple_pull_5f558 */
/* Reconstructed net_buf_simple_pull_5f558 @ 0x5f558  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void net_buf_simple_pull_5f558(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned short ushort_val = *(unsigned short*)((char*)param_1 + 4);
    if (ushort_val < param_2) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "buf->len >= len" /*=0xf5474*/, "WEST_TOPDIR/zephyr/subsys/net/buf_simple.c" /*=0xf543a*/, 0x18dU, param_4);
        unsigned long long rv = assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf_simple.c" /*=0xf543a*/, 0x18dU);
        unsigned int r0v = (unsigned int)rv;
        unsigned int r1v = (unsigned int)(rv >> 32);
        unsigned int r2v = "WEST_TOPDIR/zephyr/subsys/net/buf_simple.c" /*=0xf543a*/ - r1v;
        *(volatile unsigned short*)(r0v + 4) = (unsigned short)r2v;
        unsigned int memv = *(volatile unsigned int*)r0v;
        unsigned int finalv = memv + r1v;
        *(volatile unsigned int*)0x18dUL = finalv;
        return;
    }
    *(unsigned short*)((char*)param_1 + 4) = (unsigned short)(ushort_val - param_2);
    *param_1 = *param_1 + param_2;
    return;
}

