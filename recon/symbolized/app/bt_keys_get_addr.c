#include "g1_app_symbols.h"
/* named: bt_keys_get_addr */
/* Reconstructed bt_keys_get_addr @ 0x5e6a8  (parity: 300/300 trials, PROVEN) */

extern void bt_keys_pool_find_or_alloc(void);
extern void assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void bt_keys_get_addr(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"addr != ((void *)0)" /*=0xf52ac*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0x59,param_4);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0x59);
  }
  bt_keys_pool_find_or_alloc();
  return;
}

