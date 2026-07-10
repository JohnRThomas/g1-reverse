#include "g1_app_symbols.h"
/* named: bt_keys_get_type */
/* Reconstructed bt_keys_get_type @ 0x5e9d0  (parity: 300/300 trials, PROVEN) */

extern int printk(int a,int b,int c,int d,int e);
extern void assert_post_action(int a,int b);
extern int bt_keys_find(void);
extern int bt_keys_get_addr(int a,int b);
extern void bt_keys_add_type(int a,int b);
int bt_keys_get_type(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  if (param_3 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"addr != ((void *)0)" /*=0xf52ac*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0xd2,param_4);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0xd2);
  }
  iVar1 = bt_keys_find();
  if (iVar1 == 0 && (iVar1 = bt_keys_get_addr(param_2,param_3), iVar1 != 0)) {
    bt_keys_add_type(iVar1,param_1);
  }
  return iVar1;
}

