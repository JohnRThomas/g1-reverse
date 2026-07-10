#include "g1_app_symbols.h"
/* named: FUN_000569a0 */
/* globals referenced:
//   0x20006138  g_ble_conn_pool              
*/
/* Reconstructed FUN_000569a0 @ 0x569a0  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);

unsigned int FUN_000569a0(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int diff = param_1 - (int)((uintptr_t)&g_ble_conn_pool) /*=0x20006138*/;
    int shifted = diff >> 3;
    unsigned int R = (0x684bda13U * (unsigned int)shifted) & 0xffU;
    if (param_1 != (int)((uintptr_t)&g_ble_conn_pool) /*=0x20006138*/) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, ((uintptr_t)&rodata_f3c92) /*=0xf3c92*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x543UL);
        printk("\tInvalid bt_conn pointer\n" /*=0xf3d5b*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x543UL, 0x543UL);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x543UL);
        return 0x543U & 0xffU;
    }
    return R;
}

