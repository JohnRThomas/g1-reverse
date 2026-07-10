#include "g1_app_symbols.h"
/* named: bt_keys_add_type */
/* Reconstructed bt_keys_add_type @ 0x5e9a0  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

void bt_keys_add_type(int param_1, unsigned short param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "keys != ((void *)0)" /*=0xf5298*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/, 0x12a, param_4);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/, 0x12a);
  }
  *(volatile unsigned short *)(param_1 + 0xe) = param_2 | *(volatile unsigned short *)(param_1 + 0xe);
}

