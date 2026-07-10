#include "g1_app_symbols.h"
/* named: FUN_00051c68 */
/* Reconstructed FUN_00051c68 @ 0x51c68  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void FUN_00051c68(void)
{
  unsigned int uVar1;

  uVar1 = "WEST_TOPDIR/zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/include/mgmt/mcumgr/grp/img_mgmt/img_mgmt_priv.h" /*=0xf2561*/;
  printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"slot >= 0 && slot < (2 << 1)" /*=0xf25c5*/,"WEST_TOPDIR/zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/include/mgmt/mcumgr/grp/img_mgmt/img_mgmt_priv.h" /*=0xf2561*/,0x62);
  printk("\tImpossible slot number\n" /*=0xf25e2*/,0,0,0);
  assert_post_action(uVar1,0x62);
}

